using Sharpmake;

[module: Sharpmake.Include("../../sharpmake/common.sharpmake.cs")]
[module: Sharpmake.Include("../common_lib/common_lib.library.sharpmake.cs")]

[Generate]
class leetcode_longest_string_chain_Exercise : BaseProject
{
    public leetcode_longest_string_chain_Exercise()
    {
        Name = "leetcode_longest_string_chain";

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

        conf.AddPublicDependency<CommonLibLibrary>(target);
    }
}
