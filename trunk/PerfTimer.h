// CPerfTimer - a simple Win32 performance counter wrapper
// by Dean Wyant dwyant@mindspring.com

/*

  This class is simple to use. Just declare a variable(s) as type CPerfTimer,
  call Start() to start timimg and call Stop() to stop timimg. You can pause a
  timer by calling Stop() and then you can call Start() to resume. Retrieve the
  elapsed time by calling an Elapsed..() function. Assignment, addition, 
  subtraction and comparison are supported. There are a few information calls
  available also. All calls except Start and Stop can be performed on a timer
  without stopping it.
  
*/

#ifndef __PERFTIMER_H__
#define __PERFTIMER_H__

//##ModelId=474D3037039B
class CPerfTimer
{
public:
	//##ModelId=474D303703AA
  CPerfTimer(BOOL bStart = FALSE) {Init(bStart);}

	//##ModelId=474D303703AC
  CPerfTimer(const CPerfTimer& Src); 

	//##ModelId=474D303703BB
  virtual ~CPerfTimer() {;}

	//##ModelId=474D303703C9
  void Start(BOOL bReset = FALSE);   // Start from current value or optionally from 0
	//##ModelId=474D303703D9
  void Stop();                       // Stop timing. Use Start afterwards to continue.
 
	//##ModelId=474D303703DA
  BOOL IsRunning();                  // Returns FALSE if stopped.
  
	//##ModelId=474D30380001
  BOOL IsSupported();                // Returns FALSE if performance counter not supported.
                                     // Call after constructing at least one CPerfTimer

	//##ModelId=474D30380010
  const double Resolution();         // Returns timer resolution in seconds
	//##ModelId=474D30380011
  const double Resolutionms();       // Returns timer resolution in milliseconds
	//##ModelId=474D30380020
  const double Resolutionus();       // Returns timer resolution in microseconds
  
	//##ModelId=474D30380021
  const double Elapsed();            // Returns elapsed time in seconds
	//##ModelId=474D30380030
  const double Elapsedms();          // Returns elapsed time in milliseconds 
	//##ModelId=474D3038003F
  const double Elapsedus();          // Returns elapsed time in microseconds

	//##ModelId=474D3038004F
  const CPerfTimer& operator=(const CPerfTimer& Src); // Assignment operator 

  // Math operators
	//##ModelId=474D30380051
  CPerfTimer operator+(const CPerfTimer& Src) const;
	//##ModelId=474D30380060
	CPerfTimer operator-(const CPerfTimer& Src) const;
	//##ModelId=474D30380070
	const CPerfTimer& operator+=(const CPerfTimer& Src);
	//##ModelId=474D3038007F
	const CPerfTimer& operator-=(const CPerfTimer& Src);
  // For time in seconds
	//##ModelId=474D3038008E
  CPerfTimer operator+(const double Secs) const;
	//##ModelId=474D303800AD
	CPerfTimer operator-(const double Secs) const;
	//##ModelId=474D303800BC
	const CPerfTimer& operator+=(const double Secs);
	//##ModelId=474D303800BE
	const CPerfTimer& operator-=(const double Secs);

  // Boolean comparison operators
	//##ModelId=474D303800CD
	BOOL operator<(const CPerfTimer& Src);
	//##ModelId=474D303800DC
	BOOL operator>(const CPerfTimer& Src);
	//##ModelId=474D303800EC
	BOOL operator<=(const CPerfTimer& Src);
	//##ModelId=474D303800FC
	BOOL operator>=(const CPerfTimer& Src);
  // For time in seconds
	//##ModelId=474D3038010A
  BOOL operator<(const double Secs);
	//##ModelId=474D3038011A
	BOOL operator>(const double Secs);
	//##ModelId=474D3038012A
	BOOL operator<=(const double Secs);
	//##ModelId=474D30380139
	BOOL operator>=(const double Secs);

	//##ModelId=474D3038013B
  virtual void Lock() const {;}     // Override for thread safe operation
	//##ModelId=474D3038014A
  virtual void Unlock() const {;}     // Override for thread safe operation
protected:
	//##ModelId=474D30380158
  void Init(BOOL bStart);
	//##ModelId=474D30380178
  void Copy(const CPerfTimer& Src);

private:
	//##ModelId=474D30380198
  __int64 m_Start;
	//##ModelId=474D303801B7
  static __int64 m_Freq;   // does not change while system is running
	//##ModelId=474D303801D6
  static __int64 m_Adjust; // Adjustment time it takes to Start and Stop
};

//##ModelId=474D30380204
class CPerfTimerT : public CPerfTimer
{ // You only need to use types of this class if a timer is going to be shared between threads
public:
	//##ModelId=474D30380214
  CPerfTimerT(BOOL bStart = FALSE)
  {
    m_hMutex = CreateMutex(NULL, FALSE, _T(""));
    Init(bStart);
  }

	//##ModelId=474D30380224
  CPerfTimerT(const CPerfTimerT& Src) 
  { 
    m_hMutex = CreateMutex(NULL,FALSE,_T(""));
    Copy(Src); 
  }

	//##ModelId=474D30380226
  CPerfTimerT(const CPerfTimer& Src) 
  { 
    m_hMutex = CreateMutex(NULL,FALSE,_T(""));
    Copy(Src); 
  }

	//##ModelId=474D30380233
  virtual ~CPerfTimerT() 
  { CloseHandle(m_hMutex); }

	//##ModelId=474D30380235
  const CPerfTimerT& operator=(const CPerfTimerT& Src) // Assignment operator 
  {
    Copy(Src);
    return *this; 
  }
 
	//##ModelId=474D30380243
  virtual void Lock() const { WaitForSingleObject(m_hMutex,10000); }   
	//##ModelId=474D30380245
  virtual void Unlock() const { ReleaseMutex(m_hMutex); }   
private:
	//##ModelId=474D30380253
  HANDLE m_hMutex;
};

//##ModelId=474D30380158
inline void CPerfTimer::Init(BOOL bStart)
{
  if (!m_Freq) 
  { // Initialization should only run once
    QueryPerformanceFrequency((LARGE_INTEGER *)&m_Freq); 
    if (!m_Freq)
      m_Freq = 1; // Timer will be useless but will not cause divide by zero
    m_Start = 0; 
    m_Adjust = 0; 
    Start();            // Time a Stop
    Stop(); 
    m_Adjust = m_Start;
  }
  // This is the only part that normally runs
  m_Start = 0; 
  if (bStart)
    Start(); 
}

//##ModelId=474D303703AC
inline CPerfTimer::CPerfTimer(const CPerfTimer& Src)  
{
  Copy(Src);
}

//##ModelId=474D30380178
inline void CPerfTimer::Copy(const CPerfTimer& Src)
{
  if (&Src == this) 
    return; // avoid deadlock if someone tries to copy it to itself
  Src.Lock();
  Lock();
  m_Start = Src.m_Start; 
  Unlock();
  Src.Unlock();
}

//##ModelId=474D303703C9
inline void CPerfTimer::Start(BOOL bReset) 
{ // Start from current value or optionally from 0
  __int64 i;
  QueryPerformanceCounter((LARGE_INTEGER *)&i);
  Lock();
  if ((!bReset) && (m_Start < 0))
    m_Start += i;   // We are starting with an accumulated time
  else 
    m_Start = i;    // Starting from 0
  Unlock();
} 

//##ModelId=474D303703D9
inline void CPerfTimer::Stop() 
{ // Stop timing. Use Start afterwards to continue
  Lock();
  if (m_Start <= 0)
  {
    Unlock();
    return;          // Was not running
  }
  __int64 i;
  QueryPerformanceCounter((LARGE_INTEGER *)&i); 
  m_Start += -i;          // Stopped timer keeps elapsed timer ticks as a negative 
  if (m_Start < m_Adjust) // Do not overflow
    m_Start -= m_Adjust;  // Adjust for time timer code takes to run
  else 
    m_Start = 0;          // Stop must have been called directly after Start
  Unlock();
} 

//##ModelId=474D303703DA
inline BOOL CPerfTimer::IsRunning() 
{ // Returns FALSE if stopped.
  Lock();
  BOOL bRet = (m_Start > 0); // When < 0, holds elpased clicks
  Unlock();
  return bRet;   
}
//##ModelId=474D30380021
 inline const double CPerfTimer::Elapsed()
{ // Returns elapsed time in seconds
  CPerfTimer Result(*this);
  Result.Stop();
  return (double)(-Result.m_Start)/(double)m_Freq; 
}

//##ModelId=474D30380030
inline const double CPerfTimer::Elapsedms() 
{ // Returns elapsed time in milliseconds
  CPerfTimer Result(*this);
  Result.Stop();
  return (-Result.m_Start*1000.0)/(double)m_Freq; 
}

//##ModelId=474D3038003F
inline const double CPerfTimer::Elapsedus() 
{ // Returns elapsed time in microseconds
  CPerfTimer Result(*this);
  Result.Stop();
  return (-Result.m_Start * 1000000.0)/(double)m_Freq; 
}


// Assignment operator
//##ModelId=474D3038004F
inline const CPerfTimer& CPerfTimer::operator=(const CPerfTimer& Src) 
{
  Copy(Src);
  return *this; 
}


// Math operators
//##ModelId=474D30380051
inline CPerfTimer CPerfTimer::operator+(const CPerfTimer& Src) const
{
  CPerfTimer Result(*this);
  Result += Src; 
  return Result; 
}

//##ModelId=474D30380060
inline CPerfTimer CPerfTimer::operator-(const CPerfTimer& Src) const
{
  CPerfTimer Result(*this);
  Result -= Src; 
  return Result; 
}

//##ModelId=474D30380070
inline const CPerfTimer& CPerfTimer::operator+=(const CPerfTimer& Src)
{
  CPerfTimer SrcStop(Src);  // Temp is necessary in case Src is not stopped
  SrcStop.Stop();
  Lock();
  m_Start += SrcStop.m_Start;
  Unlock();
  return *this; 
}

//##ModelId=474D3038007F
inline const CPerfTimer& CPerfTimer::operator-=(const CPerfTimer& Src)
{
  CPerfTimer SrcStop(Src);  // Temp is necessary in case Src is not stopped
  SrcStop.Stop();
  Lock();
  m_Start -= SrcStop.m_Start; 
  Unlock();
  return *this; 
}

// For time in seconds
//##ModelId=474D3038008E
inline CPerfTimer CPerfTimer::operator+(const double Secs) const
{
  CPerfTimer Result(*this);
  Result += Secs; 
  return Result; 
}

//##ModelId=474D303800AD
inline CPerfTimer CPerfTimer::operator-(const double Secs) const
{
  CPerfTimer Result(*this);
  Result += Secs; 
  return Result; 
}

//##ModelId=474D303800BC
inline const CPerfTimer& CPerfTimer::operator+=(const double Secs)
{
  Lock();
  m_Start -= (__int64)(Secs*(double)m_Freq);
  Unlock();
  return *this; 
}

//##ModelId=474D303800BE
inline const CPerfTimer& CPerfTimer::operator-=(const double Secs)
{
  Lock();
  m_Start += (__int64)(Secs*(double)m_Freq);
  Unlock();
  return *this; 
}



// Boolean comparison operators
//##ModelId=474D303800CD
inline BOOL CPerfTimer::operator<(const CPerfTimer& Src)
{ 
  BOOL bRet; 
  CPerfTimer Temp(Src);
  Lock();
  if (m_Start <= 0)
  {
    Temp.Stop();
    bRet = (m_Start > Temp.m_Start); 
    Unlock();
    return bRet;
  }
  else
  if (Temp.m_Start > 0)
  {
    bRet = (m_Start < Temp.m_Start); 
    Unlock();
    return bRet;
  }
  else
  {
    Unlock();
    CPerfTimer ThisStop(*this);
    ThisStop.Stop();
    return (ThisStop.m_Start > Temp.m_Start); 
  }
}

//##ModelId=474D303800DC
inline BOOL CPerfTimer::operator>(const CPerfTimer& Src)
{ 
  BOOL bRet; 
  CPerfTimer Temp(Src);
  Lock();
  if (m_Start <= 0)
  {
    Temp.Stop();
    bRet = (m_Start < Temp.m_Start); 
    Unlock();
    return bRet;
  }
  else
  if (Temp.m_Start > 0)
  {
    bRet = (m_Start > Temp.m_Start); 
    Unlock();
    return bRet;
  }
  else
  {
    Unlock();
    CPerfTimer ThisStop(*this);
    ThisStop.Stop();
    return (ThisStop.m_Start < Temp.m_Start); 
  }
}

//##ModelId=474D303800EC
inline BOOL CPerfTimer::operator<=(const CPerfTimer& Src)
{ 
  return !(*this > Src);
}

//##ModelId=474D303800FC
inline BOOL CPerfTimer::operator>=(const CPerfTimer& Src)
{ 
  return !(*this < Src);
}

// For time in seconds
//##ModelId=474D3038010A
inline BOOL CPerfTimer::operator<(const double Secs)
{ 
  BOOL bRet; 
  Lock();
  if (m_Start <= 0)
  {
    bRet = (m_Start > (__int64)(-Secs*(double)m_Freq)); 
    Unlock();
    return bRet;
  }
  else
  {
    Unlock();
    CPerfTimer ThisStop(*this);
    ThisStop.Stop();
    return (ThisStop.m_Start > (__int64)(-Secs*(double)m_Freq)); 
  }
}

//##ModelId=474D3038011A
inline BOOL CPerfTimer::operator>(const double Secs)
{ 
  BOOL bRet; 
  Lock();
  if (m_Start <= 0)
  {
    bRet = (m_Start < (__int64)(-Secs*(double)m_Freq)); 
    Unlock();
    return bRet;
  }
  else
  {
    Unlock();
    CPerfTimer ThisStop(*this);
    ThisStop.Stop();
    return (ThisStop.m_Start < (__int64)(-Secs*(double)m_Freq)); 
  }
}

//##ModelId=474D3038012A
inline BOOL CPerfTimer::operator<=(const double Secs)
{ 
  return !(*this > Secs);
}

//##ModelId=474D30380139
inline BOOL CPerfTimer::operator>=(const double Secs)
{ 
  return !(*this < Secs);
}


#endif //__PERFTIMER_H__
