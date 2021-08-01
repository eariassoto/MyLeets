using Sharpmake;

[module: Sharpmake.Include("../sharpmake/common.sharpmake.cs")]
[module: Sharpmake.Include("fmt.library.sharpmake.cs")]

[Generate]
class External_SpdLogLibrary : CXXExternalStaticLibraryProject
{
    public External_SpdLogLibrary()
    {
        Name = "spdlog";

        ProjectSourceRoot = @"[project.ProjectRoot]";
        ProjectIncludeRoot = @"[project.ProjectRoot]/include";

        SourceFilesIncludeRegex.Add(@"src[/\\]");
        SourceFilesFiltersRegex.Add(@"src[/\\]");

        SourceFilesIncludeRegex.Add(@"include[/\\]");
        SourceFilesFiltersRegex.Add(@"include[/\\]");

        AddTargets(
            new Target(
                Platform.win32 | Platform.win64,
                DevEnv.vs2019,
                Optimization.Debug | Optimization.Release
            )
        );
    }

    public override void ConfigureAll(Project.Configuration conf, Target target)
    {
        base.ConfigureAll(conf, target);

        conf.AddPublicDependency<External_FmtLibrary>(target);

        conf.Defines.Add("SPDLOG_COMPILED_LIB", "SPDLOG_FMT_EXTERNAL");
    }
}
