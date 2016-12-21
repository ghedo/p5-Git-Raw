#include "diff_generate.h"
void test_diff_format_email__with_message(void)
{
	git_diff_format_email_options opts = GIT_DIFF_FORMAT_EMAIL_OPTIONS_INIT;
	const char *email = "From 627e7e12d87e07a83fad5b6bfa25e86ead4a5270 Mon Sep 17 00:00:00 2001\n" \
	"From: Patrick Steinhardt <ps@pks.im>\n" \
	"Date: Tue, 24 Nov 2015 13:34:39 +0100\n" \
	"Subject: [PATCH] Modify content with message\n" \
	"\n" \
	"Modify content of file3.txt by appending a new line. Make this\n" \
	"commit message somewhat longer to test behavior with newlines\n" \
	"embedded in the message body.\n" \
	"\n" \
	"Also test if new paragraphs are included correctly.\n" \
	"---\n" \
	" file3.txt | 1 +\n" \
	" 1 file changed, 1 insertion(+)\n" \
	"\n" \
	"diff --git a/file3.txt b/file3.txt\n" \
	"index 9a2d780..7309653 100644\n" \
	"--- a/file3.txt\n" \
	"+++ b/file3.txt\n" \
	"@@ -3,3 +3,4 @@ file3!\n" \
	" file3\n" \
	" file3\n" \
	" file3\n" \
	"+file3\n" \
	"--\n" \
	"libgit2 " LIBGIT2_VERSION "\n" \
	"\n";

	opts.body = "Modify content of file3.txt by appending a new line. Make this\n" \
	"commit message somewhat longer to test behavior with newlines\n" \
	"embedded in the message body.\n" \
	"\n" \
	"Also test if new paragraphs are included correctly.";

	assert_email_match(
		email, "627e7e12d87e07a83fad5b6bfa25e86ead4a5270", &opts);
}


	" 2 files changed, 10 insertions(+)\n" \