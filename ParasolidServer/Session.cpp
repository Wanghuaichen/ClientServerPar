// Session.cpp: implementation of the CSession class.
//
//////////////////////////////////////////////////////////////////////


#include "Session.h"
#include "parasolid_kernel.h"
#include "frustrum_ifails.h"
#include <assert.h> 
#include <math.h>

#define VERIFY(f) assert(f)
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;

//#define new DEBUG_NEW
#endif

// The following are frustrum function declarations

extern void StartFileFrustrum( int *);
extern void AbortFrustrum( int *);
extern void StopFileFrustrum( int *);
extern void OpenReadFrustrumFile( const int *, const int *, const char *, const int *,
		    const int *, int *, int *);
extern void OpenWriteFrustrumFile( const int *, const int *, const char *, const int *,
		    const char *, const int *, int *, int *);
extern void CloseFrustrumFile( const int *, const int *, const int *, int *);
extern void ReadFromFrustrumFile( const int *, const int *, const int *, char *, int *,
		    int *);
extern void WriteToFrustrumFile( const int *, const int *, const int *, const char *,
		    int *);

// The following are for the delta frustrum

extern "C" {
	PK_ERROR_code_t FRU_delta_open_for_write(PK_PMARK_t, PK_DELTA_t *);
	PK_ERROR_code_t FRU_delta_open_for_read(PK_DELTA_t);
	PK_ERROR_code_t FRU_delta_write(PK_DELTA_t, unsigned, const char *);
	PK_ERROR_code_t FRU_delta_read(PK_DELTA_t, unsigned, char *);
	PK_ERROR_code_t FRU_delta_delete(PK_DELTA_t);
	PK_ERROR_code_t FRU_delta_close(PK_DELTA_t);
	int FRU__delta_init( int action );
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSession::CSession()
{
	// Start up Parasolid
	//if ( !Start() )
		//exit(0);
}

CSession::~CSession()
{
	// Close down Parasolid
	Stop();
}

// Starts up Parasolid Session, returns true is successful, false otherwise.

bool CSession::Start()
{
	bool ok = true;

	// Register frustrum functions
	// Note: the GO functions are registered in CExampleAppDoc
	
	PK_SESSION_frustrum_t fru;
	PK_SESSION_frustrum_o_m( fru );
	
	fru.fstart = StartFrustrum;
	fru.fabort = AbortFrustrum;
	fru.fstop  = StopFrustrum;
	fru.fmallo = GetMemory;
	fru.fmfree = ReturnMemory;
	fru.ffoprd = OpenReadFrustrumFile;
	fru.ffopwr = OpenWriteFrustrumFile;
	fru.ffclos = CloseFrustrumFile;
	fru.ffread = ReadFromFrustrumFile;
	fru.ffwrit = WriteToFrustrumFile;

	VERIFY( PK_SESSION_register_frustrum( &fru ) == PK_ERROR_no_errors);
	// Register Delta Frustrum

	PK_DELTA_frustrum_t delta_fru;

	delta_fru.open_for_write_fn = FRU_delta_open_for_write;
	delta_fru.open_for_read_fn = FRU_delta_open_for_read;
	delta_fru.close_fn = FRU_delta_close; 
	delta_fru.write_fn = FRU_delta_write;
	delta_fru.read_fn = FRU_delta_read;
	delta_fru.delete_fn = FRU_delta_delete;
  
	VERIFY(PK_DELTA_register_callbacks(delta_fru) == PK_ERROR_no_errors);

	// Register Error Handler
	PK_ERROR_frustrum_t errorFru;
	errorFru.handler_fn = PKerrorHandler;
	VERIFY( PK_ERROR_register_callbacks( errorFru ) == PK_ERROR_no_errors );

	// Starts the modeller

	PK_SESSION_start_o_t options;
	PK_SESSION_start_o_m( options );

	// By default session journalling is turned off, to enable set options.journal_file 
	// to where you want this data to be written to.
	// eg. 
	// options.journal_file = "c:\\temp\\test";
	
	// PK_SESSION_start also initialises the following interface parameters:
	
	//		PK_SESSION_set_check_arguments    PK_LOGICAL_true
	//		PK_SESSION_set_check_self_int     PK_LOGICAL_true
    //		PK_SESSION_set_check_continuity   PK_LOGICAL_true
	//		PK_SESSION_set_general_topology   PK_LOGICAL_false
    //		PK_SESSION_set_swept_spun_surfs   PK_LOGICAL_false
	//		PK_SESSION_set_tag_limit          0 (ie: no limit)
    //		PK_SESSION_set_angle_precision    0.00000000001
    //		PK_SESSION_set_precision          0.00000001
	
	PK_SESSION_start( &options );
	
	// Check to see if it all started up OK
	PK_LOGICAL_t was_error = PK_LOGICAL_true;
	PK_ERROR_sf_t error_sf;
	PK_ERROR_ask_last( &was_error, &error_sf );
	if ( was_error )
		return false;

	return ok;
}

bool CSession::Stop()
{
	PK_SESSION_stop();
	return true;
}

void CSession::StartFrustrum(int * ifail)
{
	*ifail = FR_no_errors;	
	FRU__delta_init( 1 );
	StartFileFrustrum( ifail );
}

void CSession::StopFrustrum(int * ifail)
{

	*ifail = FR_no_errors;
	FRU__delta_init( 2 );
	StopFileFrustrum( ifail );
}

void CSession::GetMemory(int * nBytes, char * * memory, int * ifail)
{

	*memory = new char[ *nBytes ];
	*ifail = (*memory) ? FR_no_errors : FR_memory_full;
}

void CSession::ReturnMemory(int * nBytes, char * * memory, int * ifail)
{
	delete[] *memory;
	*ifail = FR_no_errors;
}

PK_ERROR_code_t CSession::PKerrorHandler( PK_ERROR_sf_t* error )
{
	/*CString text;
	text.Format( "PK error: %s returned %s.", error->function, 
		error->code_token );
	AfxMessageBox( text.GetBuffer( 0 ) );*/
	return error->code;
}