#ifndef _COMMON_DEF_H_
#define _COMMON_DEF_H_

//Margins
#define MARGIN_LEFT				25.0f
#define MARGIN_RIGHT			25.0f
#define MARGIN_TOP				30.0f
#define MARGIN_BOTTOM			30.0f

//Page
#define DEFAULT_PAGE			4		//A4
#define DEFAULT_OPEN_MODE		0		//nont
#define DEFAULT_OPEN_ACTION		0		//Retain
#define DEFAULT_EFFECT			2		//Box

#define SIZE_POINT_STR			"Size in points: %.0fx%.0f"

//##ModelId=474D307500BC
struct _PageSpec
{
	//##ModelId=474D307500CD
	float	Right;
	//##ModelId=474D307500EB
	float	Left;
	//##ModelId=474D307500EC
	float	Top;
	//##ModelId=474D307500FB
	float	Bottom;
	//##ModelId=474D307500FC
	int		OpenMode;
	//##ModelId=474D3075010A
	int		OpenAction;
	//##ModelId=474D3075012A
	int		PageSize;
	//##ModelId=474D30750139
	int		Effect;
	//##ModelId=474D3075013A
	BOOL	Launch;
};

#endif	//_COMMON_DEF_H_
