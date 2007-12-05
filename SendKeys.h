#ifndef __SENDKEYS_04192004__INC__
#define __SENDKEYS_04192004__INC__

#include <windows.h>
#include <tchar.h>
// Please see SendKeys.cpp for copyright and usage issues.

//##ModelId=474D30250214
class CSendKeys
{
private:
  bool m_bWait, m_bUsingParens, m_bShiftDown, m_bAltDown, m_bControlDown, m_bWinDown;
  DWORD  m_nDelayAlways, m_nDelayNow;

	//##ModelId=474D30250233
  static BOOL CALLBACK enumwindowsProc(HWND hwnd, LPARAM lParam);
	//##ModelId=474D30250252
  void   CarryDelay();

	//##ModelId=474D302601F5
  typedef BYTE KEYBOARDSTATE_t[256];
	//##ModelId=474D30260224
  struct enumwindow_t
  {
		//##ModelId=474D30260243
    LPTSTR str;
		//##ModelId=474D30260262
    HWND hwnd;
  };

	//##ModelId=474D30260281
  struct key_desc_t
  {
		//##ModelId=474D302602A1
    LPCTSTR keyName;
		//##ModelId=474D302602B0
    BYTE VKey;
		//##ModelId=474D302602B1
    bool normalkey; // a normal character or a VKEY ?
  };

  enum
  {
    MaxSendKeysRecs  = 71,
    MaxExtendedVKeys = 10
  };

  /*
  Reference: VkKeyScan() / MSDN
  Bit Meaning 
  --- --------
  1   Either SHIFT key is pressed. 
  2   Either CTRL key is pressed. 
  4   Either ALT key is pressed. 
  8   The Hankaku key is pressed 
  16  Reserved (defined by the keyboard layout driver). 
  32  Reserved (defined by the keyboard layout driver). 
  */
	//##ModelId=474D30250253
  static const WORD VKKEYSCANSHIFTON;
	//##ModelId=474D30250291
  static const WORD VKKEYSCANCTRLON;
	//##ModelId=474D302502B0
  static const WORD VKKEYSCANALTON;
	//##ModelId=474D302502CF
  static const WORD INVALIDKEY;

	//##ModelId=474D302502F0
  static key_desc_t KeyNames[MaxSendKeysRecs]; 
	//##ModelId=474D3025031E
  static const BYTE ExtendedVKeys[MaxExtendedVKeys];

	//##ModelId=474D3025035C
  static bool BitSet(BYTE BitTable, UINT BitMask);

	//##ModelId=474D3025038B
  void PopUpShiftKeys();

	//##ModelId=474D3025038C
  static bool IsVkExtended(BYTE VKey);
	//##ModelId=474D302503AA
  void SendKeyUp(BYTE VKey);
	//##ModelId=474D302503BA
  void SendKeyDown(BYTE VKey, WORD NumTimes, bool GenUpMsg, bool bDelay = false);
	//##ModelId=474D3026003F
  void SendKey(WORD MKey, WORD NumTimes, bool GenDownMsg);
	//##ModelId=474D3026006E
  static WORD StringToVKey(LPCTSTR KeyString, int &idx);
	//##ModelId=474D3026008D
  void KeyboardEvent(BYTE VKey, BYTE ScanCode, LONG Flags);

public:

	//##ModelId=474D302600AD
  bool SendKeys(LPCTSTR KeysString, bool Wait = false);
	//##ModelId=474D302600FB
  static bool AppActivate(HWND wnd);
	//##ModelId=474D3026011A
  static bool AppActivate(LPCTSTR WindowTitle, LPCTSTR WindowClass = 0);
	//##ModelId=474D30260168
  void SetDelay(const DWORD delay) { m_nDelayAlways = delay; }
	//##ModelId=474D302601B7
  CSendKeys();
};

#endif
