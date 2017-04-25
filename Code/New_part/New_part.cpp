//New_part

// Mandatory UF Includes
#include <uf.h>
#include <uf_object_types.h>

// Internal Includes
#include <NXOpen/ListingWindow.hxx>
#include <NXOpen/NXMessageBox.hxx>
#include <NXOpen/UI.hxx>

// Internal+External Includes
#include <NXOpen/Annotations.hxx>
#include <NXOpen/Assemblies_Component.hxx>
#include <NXOpen/Assemblies_ComponentAssembly.hxx>
#include <NXOpen/Body.hxx>
#include <NXOpen/BodyCollection.hxx>
#include <NXOpen/Face.hxx>
#include <NXOpen/Line.hxx>
#include <NXOpen/NXException.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Session.hxx>

//用户自定义头文件
#include <time.h> 
#include <NXOpen/FileNew.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <uf.h> 
#include <uf_ui.h> 
/*#include <WinNT.h>*/
#include "limits.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <map>
#include "INIParser.h"




// Std C++ Includes
#include <iostream>
#include <sstream>

using namespace NXOpen;
using std::string;
using std::exception;
using std::stringstream;
using std::endl;
using std::cout;
using std::cerr;

//------------------------------------------------------------------------------
// NXOpen c++ test class 
//------------------------------------------------------------------------------
class MyClass
{
    // class members
public:
    static Session *theSession;
    static UI *theUI;

    MyClass();
    ~MyClass();

	void do_it();
	void print(const NXString &);
	void print(const string &);
	void print(const char*);

private:
	Part *workPart, *displayPart;
	NXMessageBox *mb;
	ListingWindow *lw;
};

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(MyClass::theSession) = NULL;
UI *(MyClass::theUI) = NULL;

//------------------------------------------------------------------------------
// Constructor 
//------------------------------------------------------------------------------
MyClass::MyClass()
{

	// Initialize the NX Open C++ API environment
	MyClass::theSession = NXOpen::Session::GetSession();
	MyClass::theUI = UI::GetUI();
	mb = theUI->NXMessageBox();
	lw = theSession->ListingWindow();

    workPart = theSession->Parts()->Work();
	displayPart = theSession->Parts()->Display();
	
}

//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
MyClass::~MyClass()
{
}

//------------------------------------------------------------------------------
// Print string to listing window or stdout
//------------------------------------------------------------------------------
void MyClass::print(const NXString &msg)
{
	if(! lw->IsOpen() ) lw->Open();
	lw->WriteLine(msg);
}
void MyClass::print(const string &msg)
{
	if(! lw->IsOpen() ) lw->Open();
	lw->WriteLine(msg);
}
void MyClass::print(const char * msg)
{
	if(! lw->IsOpen() ) lw->Open();
	lw->WriteLine(msg);
}




//------------------------------------------------------------------------------
// Do something
//------------------------------------------------------------------------------
void MyClass::do_it()
{

// TODO: add your code here

// 读INI文件,NI文件如下
// 	[BuildNewpart]
// 	Prefix=Yang
// 	path=F:\\NX\\
//===============读INI配置文件==================================
	INIParser ini_parser;
	ini_parser.ReadINI("D:\\YX_Tools\\Configure\\config.ini");//INI文件路径
	string FilePrefix=ini_parser.GetValue("BuildNewpart", "Prefix");//文件名前缀
	string FilePath=ini_parser.GetValue("BuildNewpart", "path");//保存路径
	ini_parser.Clear();
	ini_parser.GetSize() ;
//===============获取当前系统时间==================================
	time_t  t = time(0); 
	char file_name[64]; 
	strftime( file_name, sizeof(file_name), "%Y%m%d%H%M",localtime(&t) ); 
	puts( file_name ); 
	
	string file_path_name=FilePath+FilePrefix+"-"+file_name+".prt";//最终文件名=路径+前缀+时间+.prt
	const char* FileName = file_path_name.data();//string转char*,file_path_name是string类型,FileName是char*类型
//===============输出测试==================================
//				UF_initialize();
// 			const char* File_Prefix = FilePrefix.data();
// 			const char* File_Path = FilePath.data();

// 			UF_UI_open_listing_window();
// 			UF_UI_write_listing_window(File_Prefix);
// 			UF_UI_write_listing_window("\n");
// 			UF_UI_write_listing_window(File_Path);	
// 			UF_UI_write_listing_window("\n");
// 			UF_UI_write_listing_window(FileName);
// 			UF_terminate();
//================新建文件=================================
	NXOpen::FileNew *fileNew1;
	fileNew1 = theSession->Parts()->FileNew();
	fileNew1->SetTemplateFileName("model-plain-1-mm-template.prt");
	fileNew1->SetUseBlankTemplate(false);
	fileNew1->SetApplicationName("ModelTemplate");
	fileNew1->SetUnits(NXOpen::Part::UnitsMillimeters);
	fileNew1->SetRelationType("");
	fileNew1->SetUsesMasterModel("No");
	fileNew1->SetTemplateType(NXOpen::FileNewTemplateTypeItem);
	fileNew1->SetTemplatePresentationName(NXString("\346\250\241\345\236\213", NXString::UTF8));
	fileNew1->SetItemType("");
	fileNew1->SetSpecialization("");
	fileNew1->SetCanCreateAltrep(false);
	fileNew1->SetNewFileName(FileName);
	fileNew1->SetMasterFileName("");
	fileNew1->SetMakeDisplayedPart(true);
	NXOpen::NXObject *nXObject1;
	nXObject1 = fileNew1->Commit();
	NXOpen::Part *workPart(theSession->Parts()->Work());
	NXOpen::Part *displayPart(theSession->Parts()->Display());
	fileNew1->Destroy();
	theSession->ApplicationSwitchImmediate("UG_APP_GATEWAY");
	theSession->ApplicationSwitchImmediate("UG_APP_MODELING");
}

//------------------------------------------------------------------------------
// Entry point(s) for unmanaged internal NXOpen C/C++ programs
//------------------------------------------------------------------------------
//  Explicit Execution
extern "C" DllExport void ufusr( char *parm, int *returnCode, int rlen )
{
    try
    {
		// Create NXOpen C++ class instance
		MyClass *theMyClass;
		theMyClass = new MyClass();
		theMyClass->do_it();
		delete theMyClass;
	}
    catch (const NXException& e1)
    {
		UI::GetUI()->NXMessageBox()->Show("NXException", NXOpen::NXMessageBox::DialogTypeError, e1.Message());
    }
	catch (const exception& e2)
    {
		UI::GetUI()->NXMessageBox()->Show("Exception", NXOpen::NXMessageBox::DialogTypeError, e2.what());
    }
	catch (...)
    {
		UI::GetUI()->NXMessageBox()->Show("Exception", NXOpen::NXMessageBox::DialogTypeError, "Unknown Exception.");
    }
}


//------------------------------------------------------------------------------
// Unload Handler
//------------------------------------------------------------------------------
extern "C" DllExport int ufusr_ask_unload()
{
	return (int)NXOpen::Session::LibraryUnloadOptionImmediately;
}


