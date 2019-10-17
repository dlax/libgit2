/*
 * libgit2 "apply" example - shows how to use the apply API
 *
 * Written by the libgit2 contributors
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software. If not, see
 * <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include "common.h"

struct opts {
	const char *patch;
};
static void parse_opts(struct opts *o, int argc, char *argv[]);


int lg2_apply(git_repository *repo, int argc, char *argv[])
{
	struct opts o = { 0 };
	git_diff *diff;
	char *patch_content;

	parse_opts(&o, argc, argv);
	patch_content = read_file(o.patch);

	git_diff_from_buffer(&diff, patch_content, strlen(patch_content));
	if (diff == NULL)
		fprintf(stderr, "failed to parse patch\n");
	check_lg2(
		git_apply(repo, diff, GIT_APPLY_LOCATION_WORKDIR, NULL),
		"Could not apply patch", NULL);

	return 0;
}

static void usage(const char *message, const char *arg)
{
	if (message && arg)
		fprintf(stderr, "%s: %s\n", message, arg);
	else if (message)
		fprintf(stderr, "%s\n", message);
	fprintf(stderr, "usage: apply <patch>\n");
	exit(1);
}

static void parse_opts(struct opts *o, int argc, char *argv[])
{
	if (argc != 2)
		usage("Invalid argument set", NULL);
	o->patch = argv[1];
}
