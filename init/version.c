/*
 *  linux/init/version.c
 *
 *  Copyright (C) 1992  Theodore Ts'o
 *
 *  May be freely distributed as part of Linux.
 */

#include <generated/compile.h>
#include <linux/module.h>
#include <linux/uts.h>
#include <linux/utsname.h>
#include <generated/utsrelease.h>
#include <linux/version.h>
#include <linux/proc_ns.h>


#define UTS_RELEASE_MOD			UTS_RELEASE

//#define LINUX_COMPILE_BY_MOD		LINUX_COMPILE_BY
#define LINUX_COMPILE_BY_MOD		"DB"

//#define LINUX_COMPILE_HOST_MOD	LINUX_COMPILE_HOST
#define LINUX_COMPILE_HOST_MOD		"Gavin"

#define LINUX_COMPILER_MOD		LINUX_COMPILER

//#define UTS_VERSION_MOD		UTS_VERSION
#define UTS_VERSION_MOD			"#Lo SMP PREEMPT Tue Jan 1 00:00:00 CST 2019"


#ifndef CONFIG_KALLSYMS
#define version(a) Version_ ## a
#define version_string(a) version(a)

extern int version_string(LINUX_VERSION_CODE);
int version_string(LINUX_VERSION_CODE);
#endif

struct uts_namespace init_uts_ns = {
	.kref = {
		.refcount	= ATOMIC_INIT(2),
	},
	.name = {
		.sysname	= UTS_SYSNAME,
		.nodename	= UTS_NODENAME,
		.release	= UTS_RELEASE_MOD,
		.version	= UTS_VERSION_MOD,
		.machine	= UTS_MACHINE,
		.domainname	= UTS_DOMAINNAME,
	},
	.user_ns = &init_user_ns,
	.ns.inum = PROC_UTS_INIT_INO,
#ifdef CONFIG_UTS_NS
	.ns.ops = &utsns_operations,
#endif
};
EXPORT_SYMBOL_GPL(init_uts_ns);

/* FIXED STRINGS! Don't touch! */
const char linux_banner[] =
	"Linux version " UTS_RELEASE_MOD " (" LINUX_COMPILE_BY_MOD "@"
	LINUX_COMPILE_HOST_MOD ") (" LINUX_COMPILER_MOD ") " UTS_VERSION_MOD "\n";

const char linux_proc_banner[] =
	"%s version %s"
	" (" LINUX_COMPILE_BY_MOD "@" LINUX_COMPILE_HOST_MOD ")"
	" (" LINUX_COMPILER_MOD ") %s\n";
