//Owner: Dennis Lin
//Update date: 2019/03/19

//How to use:

//Add each function into ETS program native function before return statement
//For example, AutoIGRR_OnTestInit() needs to be out in OnTestInit().
//And remove all msSetSites() statement in program.
//Finally, add these codes in OnSot() before return statement
    
//  AutoIGRR_OnSot();
//
//	if (AutoIGRR_Repeat_Counter >= 0)
//		SotValue = 'T';
//	else
//      SotValue = 'Q';
//
//  return SotValue;

#define AutoIGRR_nnna 0
#define AutoIGRR_nnan 1
#define AutoIGRR_nnaa 2
#define AutoIGRR_nann 3
#define AutoIGRR_nana 4
#define AutoIGRR_naan 5
#define AutoIGRR_naaa 6
#define AutoIGRR_annn 7
#define AutoIGRR_anna 8
#define AutoIGRR_anan 9
#define AutoIGRR_anaa 10
#define AutoIGRR_aann 11
#define AutoIGRR_aana 12
#define AutoIGRR_aaan 13
#define AutoIGRR_aaaa 14

GLOBAL int AutoIGRR_Repeat_Counter = 0;
int AutoIGRR_Wait_time = 0;
int AutoIGRR_Repeat_Counter_original = 0;
int AutoIGRR_validSiteMap[NUM_SITES];
int AutoIGRR_CurrentSiteActive = AutoIGRR_nnna;
int AutoIGRR_SiteActiveMap[15][4] = {
	{0,0,0,1},
	{0,0,1,0},
	{0,0,1,1},
	{0,1,0,0},
	{0,1,0,1},
	{0,1,1,0},
	{0,1,1,1},
	{1,0,0,0},
	{1,0,0,1},
	{1,0,1,0},
	{1,0,1,1},
	{1,1,0,0},
	{1,1,0,1},
	{1,1,1,0},
	{1,1,1,1}
};
char *AutoIGRR_LogFielName[15] = {
	"IGRR_nnna.log",
	"IGRR_nnan.log",
	"IGRR_nnaa.log",
	"IGRR_nann.log",
	"IGRR_nana.log",
	"IGRR_naan.log",
	"IGRR_naaa.log",
	"IGRR_annn.log",
	"IGRR_anna.log",
	"IGRR_anan.log",
	"IGRR_anaa.log",
	"IGRR_aann.log",
	"IGRR_aana.log",
	"IGRR_aaan.log",
	"IGRR_aaaa.log"
};

int AutoIGRR_OnTestInit(void)
{
	char PopUpWindowTitle[] = {"Please setup your repeat number"};
	char *InputDescription[] = {"Repeat (times)","Wait time(ms)"};
	int ValueArray[] = {0, 0};

	PopupIntegerDialog(PopUpWindowTitle, InputDescription, ValueArray, sizeof(ValueArray)/sizeof(int), " ");
	AutoIGRR_Repeat_Counter = ValueArray[0];
	AutoIGRR_Repeat_Counter_original = ValueArray[0];
	AutoIGRR_Wait_time = ValueArray[1];
	for (int i = 0; i < NUM_SITES; i++)
		AutoIGRR_validSiteMap[i] = AutoIGRR_SiteActiveMap[AutoIGRR_nnna][i];
	msSetSites( NUM_SITES, AutoIGRR_validSiteMap );
	LogSetFileName(AutoIGRR_LogFielName[AutoIGRR_nnna], TRUE);

	return 0;
}

int AutoIGRR_OnSot(void)
{
	if (AutoIGRR_Repeat_Counter == 0)
	{
		AutoIGRR_CurrentSiteActive++;
		if (AutoIGRR_CurrentSiteActive <= AutoIGRR_aaaa)
		{
			AutoIGRR_Repeat_Counter = AutoIGRR_Repeat_Counter_original;
			for (int i = 0; i < NUM_SITES; i++)
				AutoIGRR_validSiteMap[i] = AutoIGRR_SiteActiveMap[AutoIGRR_CurrentSiteActive][i];
			msSetSites( NUM_SITES, AutoIGRR_validSiteMap );
			LogSetFileName(AutoIGRR_LogFielName[AutoIGRR_CurrentSiteActive], TRUE);
		}
		else
			AutoIGRR_Repeat_Counter = -1;
	}
	return 0;
}

int AutoIGRR_OnTestCompletion(void)
{
	AutoIGRR_Repeat_Counter--;
	lwait(AutoIGRR_Wait_time ms);

	return 0;
}