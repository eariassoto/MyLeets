using System;
using Sharpmake;

abstract class BaseSolution : Solution
{
    public string SolutionRoot = Globals.RootDirectory.Replace(@"\", @"/");
    public string SharpmakeRoot = Globals.SharpmakeDirectory;

    public BaseSolution()
    {
    }

    [Configure]
    public virtual void ConfigureAll(Solution.Configuration conf, Target target)
    {
        conf.Name = @"[target.Optimization]";
        
        if (target.DevEnv == DevEnv.vs2019)
        {
            conf.SolutionPath = @"[solution.SharpmakeRoot]/generated/solutions/";
            conf.SolutionFileName = @"[solution.Name]_[target.DevEnv]";
        }
    }
}

abstract class BaseProject : Project
{
    public string SolutionRoot = Globals.RootDirectory.Replace(@"\", @"/");
    public string SharpmakeRoot = Globals.SharpmakeDirectory;
    public string SourcePath = @"[project.SolutionRoot]/exercises";
    public string ProjectRoot = @"[project.SourcePath]/[project.Name]";
    public string ProjectSourceRoot = @"[project.ProjectRoot]/[project.Name]";
    public string ProjectIncludeRoot = @"[project.ProjectRoot]/[project.Name]";

    public BaseProject()
    {
        SourceRootPath = @"[project.ProjectSourceRoot]";
        
        // Add this custom property because Vcpkg tries to read the target name and the current nanes makes it throw this error
        // 1>Vcpkg is unable to link because we cannot decide between Release and Debug libraries. Please define the property VcpkgConfiguration to be 'Release' or 'Debug' (currently 'Editor_Debug').
        // Refer to: https://github.com/ubisoft/Sharpmake/issues/106
        CustomProperties.Add("VcpkgEnabled", "false");
    }

    [Configure]
    public virtual void ConfigureAll(Project.Configuration conf, Target target)
    {
        // This is the name of the configuration. By default, it is set to
        // [target.Optimization] (so Debug or Release), but both the debug and
        // release configurations have both a shared and a static version so
        // that would not create unique configuration names.
        conf.Name = @"[target.Optimization]";

        // MSVC SETTINGS
        if (target.DevEnv == DevEnv.vs2019)
        {
            conf.Options.Add(Options.Vc.General.WindowsTargetPlatformVersion.Latest);
            conf.Options.Add(Options.Vc.General.PreferredToolArchitecture.x64);

            conf.Options.Add(Options.Vc.General.WarningLevel.Level3);
            conf.Options.Add(Options.Vc.General.TreatWarningsAsErrors.Enable);
            conf.Options.Add(Options.Vc.General.DebugInformation.ProgramDatabase);

            conf.Options.Add(Options.Vc.Compiler.FloatingPointModel.Fast);
            conf.Options.Add(Options.Vc.Compiler.RTTI.Enable);
            conf.Options.Add(Options.Vc.Compiler.MinimalRebuild.Disable);
            conf.Options.Add(Options.Vc.Compiler.Exceptions.EnableWithSEH);
            conf.Options.Add(Options.Vc.Compiler.Inline.Default);
            conf.Options.Add(Options.Vc.Compiler.CppLanguageStandard.CPP17);
            conf.Options.Add(new Options.Vc.Compiler.DisableSpecificWarnings("4067"));
            conf.Options.Add(new Options.Vc.Compiler.DisableSpecificWarnings("4100"));
            conf.Options.Add(new Options.Vc.Compiler.DisableSpecificWarnings("4251"));
            conf.Options.Add(new Options.Vc.Compiler.DisableSpecificWarnings("4005"));

            conf.Options.Add(Options.Vc.Linker.GenerateDebugInformation.Enable);
            conf.Options.Add(Options.Vc.Linker.GenerateMapFile.Disable);
        }
        
        conf.IncludePaths.Add(@"[project.ProjectRoot]");
        conf.IncludePaths.Add(@"[project.ProjectIncludeRoot]");

        // Gives a unique path for the project because Visual Studio does not
        // like shared intermediate directories.
        conf.ProjectPath = @"[project.SharpmakeRoot]/generated/projects/[target.DevEnv]";
        conf.TargetPath = @"[project.SharpmakeRoot]/target//[target.DevEnv]/[project.Name]";
        conf.IntermediatePath = @"[project.SharpmakeRoot]/generated/intermediate/[target.DevEnv]/[project.Name]";
    }

    [Configure(Platform.win64)]
    public virtual void PlatformWin64(Configuration conf, Target target)
    {
        conf.Defines.Add("_WINDOWS", "WIN64", "_WIN64");
    }

    [Configure(Optimization.Debug)]
    public virtual void ConfigureDebug(Configuration conf, Target target)
    {
        conf.DefaultOption = Options.DefaultTarget.Debug;

        conf.Options.Add(Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDebugDLL);

        conf.Defines.Add("_DEBUG");
    }

    [Configure(Optimization.Release)]
    public virtual void ConfigureRelease(Configuration conf, Target target)
    {
        conf.DefaultOption = Options.DefaultTarget.Release;

        conf.Defines.Add("_RELEASE");
    }
}

abstract class CXXStaticLibraryProject : BaseProject
{
    public CXXStaticLibraryProject()
    {
    }

    public override void ConfigureAll(Project.Configuration conf, Target target)
    {
        base.ConfigureAll(conf, target);

        // We want this to output a static library. (LIB)
        conf.Output = Configuration.OutputType.Lib;
    }
}

abstract class CXXExternalStaticLibraryProject : CXXStaticLibraryProject
{
    public CXXExternalStaticLibraryProject()
    {
        ProjectRoot = @"[project.SolutionRoot]/external/[project.Name]";
    }

    public override void ConfigureAll(Project.Configuration conf, Target target)
    {
        base.ConfigureAll(conf, target);

        conf.SolutionFolder = "external";
    }
}
