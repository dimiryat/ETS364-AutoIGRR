//Owner: Dennis Lin
//Update date: 2019/03/19

//How to use:

//Add each function into ETS program native function before return statement
//For example, AutoIGRR_OnTestInit() needs to be out in OnTestInit().
//But for AutoIGRR_OnSot, it needs to be added as parameter of return statement.
//i.e. return AutoIGRR_OnSot(SotValue)
//And remove all msSetSites() statement in program.

int AutoIGRR_Repeat_Counter = 0;
int AutoIGRR_Wait_time = 0;
int AutoIGRR_Repeat_Counter_original = 0;
int AutoIGRR_validSiteMap[NUM_SITES];
int AutoIGRR_CurrentSiteActive = 0;

#if (NUM_SITES==2)
#define FirstCombination 0
#define LastCombination 2
int AutoIGRR_SiteActiveMap[3][2] = {
	{0,1},
	{1,0},
	{1,1}
};
char *AutoIGRR_LogFielName[3] = {
	"IGRR_na.log",
	"IGRR_an.log",
	"IGRR_aa.log"
};
#endif

#if (NUM_SITES==4)
#define FirstCombination 0
#define LastCombination 14
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
#endif

#if (NUM_SITES==8)
#define FirstCombination 0
#define LastCombination 22
int AutoIGRR_SiteActiveMap[23][8] = {
	{1,0,0,0,1,0,0,0},
	{0,1,0,0,0,1,0,0},
	{1,1,0,0,1,1,0,0},
	{0,0,1,0,0,0,1,0},
	{1,0,1,0,1,0,1,0},
	{0,1,1,0,0,1,1,0},
	{1,1,1,0,1,1,1,0},
	{0,0,0,1,0,0,0,1},
	{1,0,0,1,1,0,0,1},
	{0,1,0,1,0,1,0,1},
	{1,1,0,1,1,1,0,1},
	{0,0,1,1,0,0,1,1},
	{1,0,1,1,1,0,1,1},
	{0,1,1,1,0,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0},
	{0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,0,0},
	{0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,1}
};
char *AutoIGRR_LogFielName[23] = {
	"IGRR_annnannn.log",
	"IGRR_nannnann.log",
	"IGRR_aannaann.log",
	"IGRR_nnannnan.log",
	"IGRR_anananan.log",
	"IGRR_naannaan.log",
	"IGRR_aaanaaan.log",
	"IGRR_nnnannna.log",
	"IGRR_annaanna.log",
	"IGRR_nananana.log",
	"IGRR_aanaaana.log",
	"IGRR_nnaannaa.log",
	"IGRR_anaaanaa.log",
	"IGRR_naaanaaa.log",
	"IGRR_aaaaaaaa.log",
	"IGRR_annnnnnn.log",
	"IGRR_nannnnnn.log",
	"IGRR_nnannnnn.log",
	"IGRR_nnnannnn.log",
	"IGRR_nnnnannn.log",
	"IGRR_nnnnnann.log",
	"IGRR_nnnnnnan.log",
	"IGRR_nnnnnnna.log",
};
#endif

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
		AutoIGRR_validSiteMap[i] = AutoIGRR_SiteActiveMap[FirstCombination][i];
	msSetSites( NUM_SITES, AutoIGRR_validSiteMap );
	LogSetFileName(AutoIGRR_LogFielName[FirstCombination], TRUE);

	return 0;
}

int AutoIGRR_OnSot(int SotValue)
{
	if (AutoIGRR_Repeat_Counter == 0)
	{
		AutoIGRR_CurrentSiteActive++;
		if (AutoIGRR_CurrentSiteActive <= LastCombination)
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
	if (AutoIGRR_Repeat_Counter >= 0)
		SotValue = 'T';
	else
	{
		SotValue = 'Q';
		LogSetFileName("Junk.log", TRUE);
	}
	return SotValue;
}

int AutoIGRR_OnTestCompletion(void)
{
	AutoIGRR_Repeat_Counter--;
	lwait(AutoIGRR_Wait_time ms);

	return 0;
}