#!/usr/bin/perl

use warnings;

use strict;

my $password = $ENV{'DS_DM_PASSWORD'} || die "DS_DM_PASSWORD not set";

system("setup-ds-admin", "--silent", "--cli", "--no-prompt", "--password", $password);
