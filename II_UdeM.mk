##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=II_UdeM
ConfigurationName      :=Release
WorkspacePath          :=C:/Users/Stephantasy/Desktop/II_UdeM_UI
ProjectPath            :=C:/Users/Stephantasy/Desktop/II_UdeM_UI
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Stephantasy
Date                   :=22/02/2018
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="II_UdeM.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := $(shell wx-config --rcflags)
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  -mwindows -s $(shell wx-config --debug=no --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -O2 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
WXWIN:=C:\wxWidgets-3.1.0\
WXCFG:=gcc_dll/mswu
PATH:=C:\wxWidgets-3.1.0\lib\gcc_dll;$PATH
Objects0=$(IntermediateDirectory)/MainWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/Matrix.cpp$(ObjectSuffix) $(IntermediateDirectory)/AppLauncher.cpp$(ObjectSuffix) $(IntermediateDirectory)/MainApp.cpp$(ObjectSuffix) $(IntermediateDirectory)/MatrixWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatArchitecture.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatColorPrise.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_Categorie.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatIdSeller.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatIp.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/ii_CatLocal.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatName.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatNoPlaque.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatNoPrise.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatNoSerie.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatOs.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatPort.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatResponsable.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatSwitch.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatType.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/ii_Equipment.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_Inventory.cpp$(ObjectSuffix) $(IntermediateDirectory)/ii_CatAppartenance.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Release"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/MainWindow.cpp$(ObjectSuffix): MainWindow.cpp $(IntermediateDirectory)/MainWindow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/MainWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MainWindow.cpp$(DependSuffix): MainWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MainWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MainWindow.cpp$(DependSuffix) -MM MainWindow.cpp

$(IntermediateDirectory)/MainWindow.cpp$(PreprocessSuffix): MainWindow.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MainWindow.cpp$(PreprocessSuffix) MainWindow.cpp

$(IntermediateDirectory)/Matrix.cpp$(ObjectSuffix): Matrix.cpp $(IntermediateDirectory)/Matrix.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/Matrix.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Matrix.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Matrix.cpp$(DependSuffix): Matrix.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Matrix.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Matrix.cpp$(DependSuffix) -MM Matrix.cpp

$(IntermediateDirectory)/Matrix.cpp$(PreprocessSuffix): Matrix.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Matrix.cpp$(PreprocessSuffix) Matrix.cpp

$(IntermediateDirectory)/AppLauncher.cpp$(ObjectSuffix): AppLauncher.cpp $(IntermediateDirectory)/AppLauncher.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/AppLauncher.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AppLauncher.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AppLauncher.cpp$(DependSuffix): AppLauncher.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AppLauncher.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/AppLauncher.cpp$(DependSuffix) -MM AppLauncher.cpp

$(IntermediateDirectory)/AppLauncher.cpp$(PreprocessSuffix): AppLauncher.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AppLauncher.cpp$(PreprocessSuffix) AppLauncher.cpp

$(IntermediateDirectory)/MainApp.cpp$(ObjectSuffix): MainApp.cpp $(IntermediateDirectory)/MainApp.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/MainApp.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainApp.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MainApp.cpp$(DependSuffix): MainApp.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MainApp.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MainApp.cpp$(DependSuffix) -MM MainApp.cpp

$(IntermediateDirectory)/MainApp.cpp$(PreprocessSuffix): MainApp.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MainApp.cpp$(PreprocessSuffix) MainApp.cpp

$(IntermediateDirectory)/MatrixWindow.cpp$(ObjectSuffix): MatrixWindow.cpp $(IntermediateDirectory)/MatrixWindow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/MatrixWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MatrixWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MatrixWindow.cpp$(DependSuffix): MatrixWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MatrixWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MatrixWindow.cpp$(DependSuffix) -MM MatrixWindow.cpp

$(IntermediateDirectory)/MatrixWindow.cpp$(PreprocessSuffix): MatrixWindow.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MatrixWindow.cpp$(PreprocessSuffix) MatrixWindow.cpp

$(IntermediateDirectory)/ii_CatArchitecture.cpp$(ObjectSuffix): ii/CatArchitecture.cpp $(IntermediateDirectory)/ii_CatArchitecture.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatArchitecture.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatArchitecture.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatArchitecture.cpp$(DependSuffix): ii/CatArchitecture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatArchitecture.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatArchitecture.cpp$(DependSuffix) -MM ii/CatArchitecture.cpp

$(IntermediateDirectory)/ii_CatArchitecture.cpp$(PreprocessSuffix): ii/CatArchitecture.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatArchitecture.cpp$(PreprocessSuffix) ii/CatArchitecture.cpp

$(IntermediateDirectory)/ii_CatColorPrise.cpp$(ObjectSuffix): ii/CatColorPrise.cpp $(IntermediateDirectory)/ii_CatColorPrise.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatColorPrise.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatColorPrise.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatColorPrise.cpp$(DependSuffix): ii/CatColorPrise.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatColorPrise.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatColorPrise.cpp$(DependSuffix) -MM ii/CatColorPrise.cpp

$(IntermediateDirectory)/ii_CatColorPrise.cpp$(PreprocessSuffix): ii/CatColorPrise.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatColorPrise.cpp$(PreprocessSuffix) ii/CatColorPrise.cpp

$(IntermediateDirectory)/ii_Categorie.cpp$(ObjectSuffix): ii/Categorie.cpp $(IntermediateDirectory)/ii_Categorie.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/Categorie.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_Categorie.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_Categorie.cpp$(DependSuffix): ii/Categorie.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_Categorie.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_Categorie.cpp$(DependSuffix) -MM ii/Categorie.cpp

$(IntermediateDirectory)/ii_Categorie.cpp$(PreprocessSuffix): ii/Categorie.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_Categorie.cpp$(PreprocessSuffix) ii/Categorie.cpp

$(IntermediateDirectory)/ii_CatIdSeller.cpp$(ObjectSuffix): ii/CatIdSeller.cpp $(IntermediateDirectory)/ii_CatIdSeller.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatIdSeller.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatIdSeller.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatIdSeller.cpp$(DependSuffix): ii/CatIdSeller.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatIdSeller.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatIdSeller.cpp$(DependSuffix) -MM ii/CatIdSeller.cpp

$(IntermediateDirectory)/ii_CatIdSeller.cpp$(PreprocessSuffix): ii/CatIdSeller.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatIdSeller.cpp$(PreprocessSuffix) ii/CatIdSeller.cpp

$(IntermediateDirectory)/ii_CatIp.cpp$(ObjectSuffix): ii/CatIp.cpp $(IntermediateDirectory)/ii_CatIp.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatIp.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatIp.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatIp.cpp$(DependSuffix): ii/CatIp.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatIp.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatIp.cpp$(DependSuffix) -MM ii/CatIp.cpp

$(IntermediateDirectory)/ii_CatIp.cpp$(PreprocessSuffix): ii/CatIp.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatIp.cpp$(PreprocessSuffix) ii/CatIp.cpp

$(IntermediateDirectory)/ii_CatLocal.cpp$(ObjectSuffix): ii/CatLocal.cpp $(IntermediateDirectory)/ii_CatLocal.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatLocal.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatLocal.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatLocal.cpp$(DependSuffix): ii/CatLocal.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatLocal.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatLocal.cpp$(DependSuffix) -MM ii/CatLocal.cpp

$(IntermediateDirectory)/ii_CatLocal.cpp$(PreprocessSuffix): ii/CatLocal.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatLocal.cpp$(PreprocessSuffix) ii/CatLocal.cpp

$(IntermediateDirectory)/ii_CatName.cpp$(ObjectSuffix): ii/CatName.cpp $(IntermediateDirectory)/ii_CatName.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatName.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatName.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatName.cpp$(DependSuffix): ii/CatName.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatName.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatName.cpp$(DependSuffix) -MM ii/CatName.cpp

$(IntermediateDirectory)/ii_CatName.cpp$(PreprocessSuffix): ii/CatName.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatName.cpp$(PreprocessSuffix) ii/CatName.cpp

$(IntermediateDirectory)/ii_CatNoPlaque.cpp$(ObjectSuffix): ii/CatNoPlaque.cpp $(IntermediateDirectory)/ii_CatNoPlaque.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatNoPlaque.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatNoPlaque.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatNoPlaque.cpp$(DependSuffix): ii/CatNoPlaque.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatNoPlaque.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatNoPlaque.cpp$(DependSuffix) -MM ii/CatNoPlaque.cpp

$(IntermediateDirectory)/ii_CatNoPlaque.cpp$(PreprocessSuffix): ii/CatNoPlaque.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatNoPlaque.cpp$(PreprocessSuffix) ii/CatNoPlaque.cpp

$(IntermediateDirectory)/ii_CatNoPrise.cpp$(ObjectSuffix): ii/CatNoPrise.cpp $(IntermediateDirectory)/ii_CatNoPrise.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatNoPrise.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatNoPrise.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatNoPrise.cpp$(DependSuffix): ii/CatNoPrise.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatNoPrise.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatNoPrise.cpp$(DependSuffix) -MM ii/CatNoPrise.cpp

$(IntermediateDirectory)/ii_CatNoPrise.cpp$(PreprocessSuffix): ii/CatNoPrise.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatNoPrise.cpp$(PreprocessSuffix) ii/CatNoPrise.cpp

$(IntermediateDirectory)/ii_CatNoSerie.cpp$(ObjectSuffix): ii/CatNoSerie.cpp $(IntermediateDirectory)/ii_CatNoSerie.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatNoSerie.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatNoSerie.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatNoSerie.cpp$(DependSuffix): ii/CatNoSerie.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatNoSerie.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatNoSerie.cpp$(DependSuffix) -MM ii/CatNoSerie.cpp

$(IntermediateDirectory)/ii_CatNoSerie.cpp$(PreprocessSuffix): ii/CatNoSerie.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatNoSerie.cpp$(PreprocessSuffix) ii/CatNoSerie.cpp

$(IntermediateDirectory)/ii_CatOs.cpp$(ObjectSuffix): ii/CatOs.cpp $(IntermediateDirectory)/ii_CatOs.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatOs.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatOs.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatOs.cpp$(DependSuffix): ii/CatOs.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatOs.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatOs.cpp$(DependSuffix) -MM ii/CatOs.cpp

$(IntermediateDirectory)/ii_CatOs.cpp$(PreprocessSuffix): ii/CatOs.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatOs.cpp$(PreprocessSuffix) ii/CatOs.cpp

$(IntermediateDirectory)/ii_CatPort.cpp$(ObjectSuffix): ii/CatPort.cpp $(IntermediateDirectory)/ii_CatPort.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatPort.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatPort.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatPort.cpp$(DependSuffix): ii/CatPort.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatPort.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatPort.cpp$(DependSuffix) -MM ii/CatPort.cpp

$(IntermediateDirectory)/ii_CatPort.cpp$(PreprocessSuffix): ii/CatPort.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatPort.cpp$(PreprocessSuffix) ii/CatPort.cpp

$(IntermediateDirectory)/ii_CatResponsable.cpp$(ObjectSuffix): ii/CatResponsable.cpp $(IntermediateDirectory)/ii_CatResponsable.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatResponsable.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatResponsable.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatResponsable.cpp$(DependSuffix): ii/CatResponsable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatResponsable.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatResponsable.cpp$(DependSuffix) -MM ii/CatResponsable.cpp

$(IntermediateDirectory)/ii_CatResponsable.cpp$(PreprocessSuffix): ii/CatResponsable.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatResponsable.cpp$(PreprocessSuffix) ii/CatResponsable.cpp

$(IntermediateDirectory)/ii_CatSwitch.cpp$(ObjectSuffix): ii/CatSwitch.cpp $(IntermediateDirectory)/ii_CatSwitch.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatSwitch.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatSwitch.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatSwitch.cpp$(DependSuffix): ii/CatSwitch.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatSwitch.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatSwitch.cpp$(DependSuffix) -MM ii/CatSwitch.cpp

$(IntermediateDirectory)/ii_CatSwitch.cpp$(PreprocessSuffix): ii/CatSwitch.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatSwitch.cpp$(PreprocessSuffix) ii/CatSwitch.cpp

$(IntermediateDirectory)/ii_CatType.cpp$(ObjectSuffix): ii/CatType.cpp $(IntermediateDirectory)/ii_CatType.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatType.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatType.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatType.cpp$(DependSuffix): ii/CatType.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatType.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatType.cpp$(DependSuffix) -MM ii/CatType.cpp

$(IntermediateDirectory)/ii_CatType.cpp$(PreprocessSuffix): ii/CatType.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatType.cpp$(PreprocessSuffix) ii/CatType.cpp

$(IntermediateDirectory)/ii_Equipment.cpp$(ObjectSuffix): ii/Equipment.cpp $(IntermediateDirectory)/ii_Equipment.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/Equipment.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_Equipment.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_Equipment.cpp$(DependSuffix): ii/Equipment.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_Equipment.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_Equipment.cpp$(DependSuffix) -MM ii/Equipment.cpp

$(IntermediateDirectory)/ii_Equipment.cpp$(PreprocessSuffix): ii/Equipment.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_Equipment.cpp$(PreprocessSuffix) ii/Equipment.cpp

$(IntermediateDirectory)/ii_Inventory.cpp$(ObjectSuffix): ii/Inventory.cpp $(IntermediateDirectory)/ii_Inventory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/Inventory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_Inventory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_Inventory.cpp$(DependSuffix): ii/Inventory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_Inventory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_Inventory.cpp$(DependSuffix) -MM ii/Inventory.cpp

$(IntermediateDirectory)/ii_Inventory.cpp$(PreprocessSuffix): ii/Inventory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_Inventory.cpp$(PreprocessSuffix) ii/Inventory.cpp

$(IntermediateDirectory)/ii_CatAppartenance.cpp$(ObjectSuffix): ii/CatAppartenance.cpp $(IntermediateDirectory)/ii_CatAppartenance.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Stephantasy/Desktop/II_UdeM_UI/ii/CatAppartenance.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ii_CatAppartenance.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ii_CatAppartenance.cpp$(DependSuffix): ii/CatAppartenance.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ii_CatAppartenance.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ii_CatAppartenance.cpp$(DependSuffix) -MM ii/CatAppartenance.cpp

$(IntermediateDirectory)/ii_CatAppartenance.cpp$(PreprocessSuffix): ii/CatAppartenance.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ii_CatAppartenance.cpp$(PreprocessSuffix) ii/CatAppartenance.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


