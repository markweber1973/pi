##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Sensor
ConfigurationName      :=Debug
WorkspacePath          := "/home/mark/DezyneWorkspace/Sensor"
ProjectPath            := "/home/mark/DezyneWorkspace/Sensor"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Mark
Date                   :=27/12/15
CodeLitePath           :="/home/mark/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Sensor.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lpthread  -lwiringPi
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall -std=c++11 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/SensorMonitor.cc$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/runtime.cc$(ObjectSuffix) $(IntermediateDirectory)/pump.cc$(ObjectSuffix) 



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
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/SensorMonitor.cc$(ObjectSuffix): SensorMonitor.cc $(IntermediateDirectory)/SensorMonitor.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mark/DezyneWorkspace/Sensor/SensorMonitor.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SensorMonitor.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SensorMonitor.cc$(DependSuffix): SensorMonitor.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SensorMonitor.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/SensorMonitor.cc$(DependSuffix) -MM "SensorMonitor.cc"

$(IntermediateDirectory)/SensorMonitor.cc$(PreprocessSuffix): SensorMonitor.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SensorMonitor.cc$(PreprocessSuffix) "SensorMonitor.cc"

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mark/DezyneWorkspace/Sensor/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/runtime.cc$(ObjectSuffix): runtime.cc $(IntermediateDirectory)/runtime.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mark/DezyneWorkspace/Sensor/runtime.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/runtime.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/runtime.cc$(DependSuffix): runtime.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/runtime.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/runtime.cc$(DependSuffix) -MM "runtime.cc"

$(IntermediateDirectory)/runtime.cc$(PreprocessSuffix): runtime.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/runtime.cc$(PreprocessSuffix) "runtime.cc"

$(IntermediateDirectory)/pump.cc$(ObjectSuffix): pump.cc $(IntermediateDirectory)/pump.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/mark/DezyneWorkspace/Sensor/pump.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pump.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pump.cc$(DependSuffix): pump.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pump.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/pump.cc$(DependSuffix) -MM "pump.cc"

$(IntermediateDirectory)/pump.cc$(PreprocessSuffix): pump.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pump.cc$(PreprocessSuffix) "pump.cc"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


