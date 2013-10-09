package inc::MakeMaker;

use Moose;

extends 'Dist::Zilla::Plugin::MakeMaker::Awesome';

override _build_MakeFile_PL_template => sub {
	my ($self) = @_;

	my $template = <<'TEMPLATE';
use Devel::CheckLib;

my $def = '';
my $lib = '';

if (check_lib(lib => 'ssl')) {
	$def .= ' -DGIT_SSL';
	$lib .= ' -lssl -lcrypto';

	print "SSL support enabled\n";
}

if (check_lib(lib => 'ssh2')) {
	$def .= ' -DGIT_SSH';
	$lib .= ' -lssh2';

	print "SSH support enabled\n";
}

sub MY::c_o {
	return <<'EOS'
.c$(OBJ_EXT):
	$(CCCMD) $(CCCDLFLAGS) "-I$(PERL_INC)" $(PASTHRU_DEFINE) $(DEFINE) $*.c -o $@
EOS
}

# This Makefile.PL for {{ $distname }} was generated by Dist::Zilla.
# Don't edit it but the dist.ini used to construct it.
{{ $perl_prereq ? qq[BEGIN { require $perl_prereq; }] : ''; }}
use strict;
use warnings;
use ExtUtils::MakeMaker {{ $eumm_version }};
{{ $share_dir_block[0] }}
my {{ $WriteMakefileArgs }}

$WriteMakefileArgs{DEFINE} .= $def;
$WriteMakefileArgs{LIBS}   .= $lib;

unless (eval { ExtUtils::MakeMaker->VERSION(6.56) }) {
	my $br = delete $WriteMakefileArgs{BUILD_REQUIRES};
	my $pp = $WriteMakefileArgs{PREREQ_PM};

	for my $mod (keys %$br) {
		if (exists $pp -> {$mod}) {
			$pp -> {$mod} = $br -> {$mod}
				if $br -> {$mod} > $pp -> {$mod};
		} else {
			$pp -> {$mod} = $br -> {$mod};
		}
	}
}

delete $WriteMakefileArgs{CONFIGURE_REQUIRES}
	unless eval { ExtUtils::MakeMaker -> VERSION(6.52) };

WriteMakefile(%WriteMakefileArgs);
{{ $share_dir_block[1] }}
TEMPLATE

	return $template;
};

override _build_WriteMakefile_args => sub {
	# TODO: support Windows
	my $inc = '-Ixs/libgit2 -Ixs/libgit2/src -Ixs/libgit2/include -Ixs/libgit2/deps/http-parser -Ixs/libgit2/deps/zlib';
	my $def = '-DNO_VIZ -DSTDC -DNO_GZIP -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE';

	my @deps = glob 'xs/libgit2/deps/{http-parser,zlib}/*.c';
	my @srcs = glob 'xs/libgit2/src/{*.c,transports/*.c,unix/*.c,xdiff/*.c}';
	push @srcs, 'xs/libgit2/src/hash/hash_generic.c';
	my @objs = map { substr ($_, 0, -1) . 'o' } (@deps, @srcs);

	my $libgit2_objs = join ' ', @objs;

	return +{
		%{ super() },
		INC	=> "-I. $inc",
		LIBS	=> "-lrt",
		DEFINE	=> $def,
		CCFLAGS	=> '-Wall -Wno-unused-variable',
		OBJECT	=> "$libgit2_objs \$(O_FILES)",
	}
};

__PACKAGE__ -> meta -> make_immutable;
