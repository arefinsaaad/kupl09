#pragma once

#include "IClipAggregator.h"

//##ModelId=474D30750197
class CClipIDs : public CArrayEx<int>
{
public:
// PASTING FUNCTIONS

	// allocate an HGLOBAL of the given Format Type representing the Clip IDs in this array.
	//##ModelId=474D30750245
	HGLOBAL	Render(UINT cfType);
	// Fills "types" with the Format Types corresponding to the Clip IDs in this array.
	//##ModelId=474D30750253
	void GetTypes(CClipTypes& types);
	//##ModelId=474D30750272
	bool AggregateData(IClipAggregator &Aggregator, UINT cfType, BOOL bReverse);

// MANAGEMENT FUNCTIONS

	// returns the address of the given id in this array or NULL.
	//##ModelId=474D30750282
	long* FindID(long lID);

	// Blindly Moves IDs into the lParentID Group sequentially with the given order
	// (i.e. this does not check to see if the IDs' order conflict)
	// if( dIncrement < 0 ), this does not change the order
	//##ModelId=474D30750292
	BOOL MoveTo(long lParentID, double dFirst = 0, double dIncrement = -1);

	// reorders the "lParentID" Group, inserting before the given id.
	//  if the id cannot be found, this appends the IDs.
//	BOOL ReorderGroupInsert( long lParentID, long lInsertBeforeID = 0 );

	// Empties this array and fills it with the elements of the given group ID
	//##ModelId=474D307502DF
	BOOL LoadElementsOf(long lGroupID);

	//##ModelId=474D307502E1
	BOOL CopyTo(long lParentID);

	//##ModelId=474D307502F0
	BOOL DeleteIDs();

	//##ModelId=474D307502FE
	BOOL Export(CString csFilePath);
	
protected:
	//##ModelId=474D30750300
	BOOL CreateExportSqliteDB(CppSQLite3DB &db);

protected:
	
};
