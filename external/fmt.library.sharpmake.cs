using Sharpmake;

[module: Sharpmake.Include("../sharpmake/common.sharpmake.cs")]

[Generate]
class External_FmtLibrary : CXXExternalStaticLibraryProject
{
    public External_FmtLibrary()
    {
        Name = "fmt";

        ProjectSourceRoot = @"[project.ProjectRoot]";
        ProjectIncludeRoot = @"[project.ProjectRoot]/include";

        SourceFilesExcludeRegex.Add(@"test");
        SourceFilesExcludeRegex.Add(@"out");

        SourceFilesExclude.Add(@"[project.ProjectRoot]/src/fmt.cc");

        AddTargets(
            new Target(
                Platform.win32 | Platform.win64,
                DevEnv.vs2019,
                Optimization.Debug | Optimization.Release
            )
        );
    }

    public override void ConfigureAll(Configuration conf, Target target)
    {
        base.ConfigureAll(conf, target);

        conf.Options.Add(new Options.Vc.Compiler.DisableSpecificWarnings("4244"));
    }
}
