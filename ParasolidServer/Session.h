// Session.h: interface for the CSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SESSION_H__CD27375B_D581_11D2_8BF9_0000F8071DC8__INCLUDED_)
#define AFX_SESSION_H__CD27375B_D581_11D2_8BF9_0000F8071DC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "parasolid_kernel.h"

class CSession  
{
public:

	bool Start();
	bool Stop();

	static void ReturnMemory(int * nBytes, char * * memory, int * ifail);
	static void GetMemory(int * nBytes, char * * memory, int * ifail);
	static void StopFrustrum( int * ifail );
	static void StartFrustrum( int * ifail );
	static PK_ERROR_code_t PKerrorHandler( PK_ERROR_sf_t* error );
	
	CSession();
	~CSession();
};

#endif // !defined(AFX_SESSION_H__CD27375B_D581_11D2_8BF9_0000F8071DC8__INCLUDED_)
