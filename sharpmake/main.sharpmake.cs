// Copyright (c) 2021 Emmanuel Arias
using Sharpmake;
using System.IO;

[module: Sharpmake.Include("common.sharpmake.cs")]

[module: Sharpmake.Include("../exercises/cci_1_1_is_unique/cci_1_1_is_unique.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_1_2_check_permutation/cci_1_2_check_permutation.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_1_3_urlify/cci_1_3_urlify.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_1_4_palindrome_permutation/cci_1_4_palindrome_permutation.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_1_5_one_away/cci_1_5_one_away.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_1_6_string_compressor/cci_1_6_string_compressor.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_1_7_rotate_matrix/cci_1_7_rotate_matrix.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_1_8_zero_matrix/cci_1_8_zero_matrix.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_1_9_string_rotation/cci_1_9_string_rotation.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_2_1_delete_duplicates/cci_2_1_delete_duplicates.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_2_2_return_kth_to_last/cci_2_2_return_kth_to_last.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_2_3_delete_middle_node/cci_2_3_delete_middle_node.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_2_4_partition/cci_2_4_partition.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_2_5_sum_lists_least_sig_first/cci_2_5_sum_lists_least_sig_first.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_2_5_sum_lists_most_sig_first/cci_2_5_sum_lists_most_sig_first.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_2_6_palindrom_linked_list/cci_2_6_palindrom_linked_list.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/cci_2_7_intersection/cci_2_7_intersection.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/geeksforgeeks_longest_substr_k_unique_char/geeksforgeeks_longest_substr_k_unique_char.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_container_most_water/leetcode_container_most_water.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_count_and_say/leetcode_count_and_say.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_divide_two_integers/leetcode_divide_two_integers.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_find_peak_element/leetcode_find_peak_element.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_group_anagrams/leetcode_group_anagrams.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_h_index/leetcode_h_index.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_letter_combinations_phone_number/leetcode_letter_combinations_phone_number.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_longest_string_chain/leetcode_longest_string_chain.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_max_area_island/leetcode_max_area_island.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_minimum_path_sum/leetcode_minimum_path_sum.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_number_of_islands/leetcode_number_of_islands.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_search_matrix_2d/leetcode_search_matrix_2d.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_string_anagram/leetcode_string_anagram.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leetcode_word_break/leetcode_word_break.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/leet_code_eval_rev_polish/leet_code_eval_rev_polish.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/mergesort/mergesort.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/palindrome_number/palindrome_number.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/reverse_integer/reverse_integer.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/two_sum_n2/two_sum_n2.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/two_sum_with_map/two_sum_with_map.application.sharpmake.cs")]
[module: Sharpmake.Include("../exercises/valid_parentheses/valid_parentheses.application.sharpmake.cs")]


namespace MyLeets
{
    [Sharpmake.Generate]
    class MyLeetsSolution : BaseSolution
    {
        public MyLeetsSolution()
        {
            Name = "MyLeets";
            AddTargets(new Target(
                Platform.win32 | Platform.win64,
                DevEnv.vs2019,
                Optimization.Debug | Optimization.Release
            ));
        }

        public override void ConfigureAll(Configuration conf, Target target)
        {
            base.ConfigureAll(conf, target);
            conf.AddProject<cci_1_1_is_unique_Exercise>(target);
            conf.AddProject<cci_1_2_check_permutation_Exercise>(target);
            conf.AddProject<cci_1_3_urlify_Exercise>(target);
            conf.AddProject<cci_1_4_palindrome_permutation_Exercise>(target);
            conf.AddProject<cci_1_5_one_away_Exercise>(target);
            conf.AddProject<cci_1_6_string_compressor_Exercise>(target);
            conf.AddProject<cci_1_7_rotate_matrix_Exercise>(target);
            conf.AddProject<cci_1_8_zero_matrix_Exercise>(target);
            conf.AddProject<cci_1_9_string_rotation_Exercise>(target);
            conf.AddProject<cci_2_1_delete_duplicates_Exercise>(target);
            conf.AddProject<cci_2_2_return_kth_to_last_Exercise>(target);
            conf.AddProject<cci_2_3_delete_middle_node_Exercise>(target);
            conf.AddProject<cci_2_4_partition_Exercise>(target);
            conf.AddProject<cci_2_5_sum_lists_least_sig_first_Exercise>(target);
            conf.AddProject<cci_2_5_sum_lists_most_sig_first_Exercise>(target);
            conf.AddProject<cci_2_6_palindrom_linked_list_Exercise>(target);
            conf.AddProject<cci_2_7_intersection_Exercise>(target);
            conf.AddProject<geeksforgeeks_longest_substr_k_unique_char_Exercise>(target);
            conf.AddProject<leetcode_container_most_water_Exercise>(target);
            conf.AddProject<leetcode_count_and_say_Exercise>(target);
            conf.AddProject<leetcode_divide_two_integers_Exercise>(target);
            conf.AddProject<leetcode_find_peak_element_Exercise>(target);
            conf.AddProject<leetcode_group_anagrams_Exercise>(target);
            conf.AddProject<leetcode_h_index_Exercise>(target);
            conf.AddProject<leetcode_letter_combinations_phone_number_Exercise>(target);
            conf.AddProject<leetcode_longest_string_chain_Exercise>(target);
            conf.AddProject<leetcode_max_area_island_Exercise>(target);
            conf.AddProject<leetcode_minimum_path_sum_Exercise>(target);
            conf.AddProject<leetcode_number_of_islands_Exercise>(target);
            conf.AddProject<leetcode_search_matrix_2d_Exercise>(target);
            conf.AddProject<leetcode_string_anagram_Exercise>(target);
            conf.AddProject<leetcode_word_break_Exercise>(target);
            conf.AddProject<leet_code_eval_rev_polish_Exercise>(target);
            conf.AddProject<mergesort_Exercise>(target);
            conf.AddProject<palindrome_number_Exercise>(target);
            conf.AddProject<reverse_integer_Exercise>(target);
            conf.AddProject<two_sum_n2_Exercise>(target);
            conf.AddProject<two_sum_with_map_Exercise>(target);
            conf.AddProject<valid_parentheses_Exercise>(target);

        }
    }
}


public static class Globals
{
    // branch root path relative to current sharpmake file location
    public const string RelativeRootPath = @"../";
    public static string RootDirectory;
    public static string SharpmakeDirectory { get { return Path.Combine(RootDirectory, "sharpmake"); } }
}

public static class main
{
    private static void ConfigureRootDirectory()
    {
        FileInfo fileInfo = Util.GetCurrentSharpmakeFileInfo();
        string rootDirectory = Path.Combine(fileInfo.DirectoryName, Globals.RelativeRootPath);
        Globals.RootDirectory = Util.SimplifyPath(rootDirectory);
    }

    [Sharpmake.Main]
    public static void SharpmakeMain(Sharpmake.Arguments arguments)
    {
        ConfigureRootDirectory();

        arguments.Generate<MyLeets.MyLeetsSolution>();
    }
}
