void test_diff_parse__empty_file(void)
{
	const char *content =
	    "---\n"
	    " file | 0\n"
	    " 1 file changed, 0 insertions(+), 0 deletions(-)\n"
	    " created mode 100644 file\n"
	    "\n"
	    "diff --git a/file b/file\n"
	    "new file mode 100644\n"
	    "index 0000000..e69de29\n"
	    "-- \n"
	    "2.20.1\n";
	git_diff *diff;

	cl_git_pass(git_diff_from_buffer(
		&diff, content, strlen(content)));
	git_diff_free(diff);
}

void test_diff_parse__no_extended_headers(void)
{
	const char *content = PATCH_NO_EXTENDED_HEADERS;
	git_diff *diff;

	cl_git_pass(git_diff_from_buffer(
		&diff, content, strlen(content)));
	git_diff_free(diff);
}

#define cl_assert_equal_i_src(i1,i2,file,func,line) clar__assert_equal(file,func,line,#i1 " != " #i2, 1, "%d", (int)(i1), (int)(i2))
static void cl_git_assert_lineinfo_(int old_lineno, int new_lineno, int num_lines, git_patch *patch, size_t hunk_idx, size_t line_idx, const char *file, const char *func, int lineno)
	cl_git_expect(git_patch_get_line_in_hunk(&line, patch, hunk_idx, line_idx), 0, file, func, lineno);
	cl_assert_equal_i_src(old_lineno, line->old_lineno, file, func, lineno);
	cl_assert_equal_i_src(new_lineno, line->new_lineno, file, func, lineno);
	cl_assert_equal_i_src(num_lines, line->num_lines, file, func, lineno);
	cl_git_assert_lineinfo_(old,new,num,p,h,l,__FILE__,__func__,__LINE__)