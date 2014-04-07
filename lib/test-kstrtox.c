#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define for_each_test(i, test)	\
	for (i = 0; i < sizeof(test) / sizeof(test[0]); i++)

struct test_fail {
	const char *str;
	unsigned int base;
};

#define DEFINE_TEST_FAIL(test)	\
	const struct test_fail test[] __initdata

#define DECLARE_TEST_OK(type, test_type)	\
	test_type {				\
		const char *str;		\
		unsigned int base;		\
		type expected_res;		\
	}

#define DEFINE_TEST_OK(type, test)	\
	const type test[] __initdata

#define TEST_FAIL(fn, type, fmt, test)					\
{									\
	unsigned int i;							\
									\
	for_each_test(i, test) {					\
		const struct test_fail *t = &test[i];			\
		type tmp;						\
		int rv;							\
									\
		tmp = 0;						\
		rv = fn(t->str, t->base, &tmp);				\
		if (rv >= 0) {						\
			WARN(1, "str '%s', base %u, expected -E, got %d/" fmt "\n",	\
				t->str, t->base, rv, tmp);		\
			continue;					\
		}							\
	}								\
}

#define TEST_OK(fn, type, fmt, test)					\
{									\
	unsigned int i;							\
									\
	for_each_test(i, test) {					\
		const typeof(test[0]) *t = &test[i];			\
		type res;						\
		int rv;							\
									\
		rv = fn(t->str, t->base, &res);				\
		if (rv != 0) {						\
			WARN(1, "str '%s', base %u, expected 0/" fmt ", got %d\n",	\
				t->str, t->base, t->expected_res, rv);	\
			continue;					\
		}							\
		if (res != t->expected_res) {				\
			WARN(1, "str '%s', base %u, expected " fmt ", got " fmt "\n",	\
				t->str, t->base, t->expected_res, res);	\
			continue;					\
		}							\
	}								\
}

static void __init test_kstrtoull_ok(void)
{
	DECLARE_TEST_OK(unsigned long long, struct test_ull);
	static DEFINE_TEST_OK(struct test_ull, test_ull_ok) = {
		{"0",	10,	0ULL},
		{"1",	10,	1ULL},
		{"127",	10,	127ULL},
		{"128",	10,	128ULL},
		{"129",	10,	129ULL},
		{"255",	10,	255ULL},
		{"256",	10,	256ULL},
		{"257",	10,	257ULL},
		{"32767",	10,	32767ULL},
		{"32768",	10,	32768ULL},
		{"32769",	10,	32769ULL},
		{"65535",	10,	65535ULL},
		{"65536",	10,	65536ULL},
		{"65537",	10,	65537ULL},
		{"2147483647",	10,	2147483647ULL},
		{"2147483648",	10,	2147483648ULL},
		{"2147483649",	10,	2147483649ULL},
		{"4294967295",	10,	4294967295ULL},
		{"4294967296",	10,	4294967296ULL},
		{"4294967297",	10,	4294967297ULL},
		{"9223372036854775807",	10,	9223372036854775807ULL},
		{"9223372036854775808",	10,	9223372036854775808ULL},
		{"9223372036854775809",	10,	9223372036854775809ULL},
		{"18446744073709551614",	10,	18446744073709551614ULL},
		{"18446744073709551615",	10,	18446744073709551615ULL},

		{"00",		8,	00ULL},
		{"01",		8,	01ULL},
		{"0177",	8,	0177ULL},
		{"0200",	8,	0200ULL},
		{"0201",	8,	0201ULL},
		{"0377",	8,	0377ULL},
		{"0400",	8,	0400ULL},
		{"0401",	8,	0401ULL},
		{"077777",	8,	077777ULL},
		{"0100000",	8,	0100000ULL},
		{"0100001",	8,	0100001ULL},
		{"0177777",	8,	0177777ULL},
		{"0200000",	8,	0200000ULL},
		{"0200001",	8,	0200001ULL},
		{"017777777777",	8,	017777777777ULL},
		{"020000000000",	8,	020000000000ULL},
		{"020000000001",	8,	020000000001ULL},
		{"037777777777",	8,	037777777777ULL},
		{"040000000000",	8,	040000000000ULL},
		{"040000000001",	8,	040000000001ULL},
		{"0777777777777777777777",	8,	0777777777777777777777ULL},
		{"01000000000000000000000",	8,	01000000000000000000000ULL},
		{"01000000000000000000001",	8,	01000000000000000000001ULL},
		{"01777777777777777777776",	8,	01777777777777777777776ULL},
		{"01777777777777777777777",	8,	01777777777777777777777ULL},

		{"0x0",		16,	0x0ULL},
		{"0x1",		16,	0x1ULL},
		{"0x7f",	16,	0x7fULL},
		{"0x80",	16,	0x80ULL},
		{"0x81",	16,	0x81ULL},
		{"0xff",	16,	0xffULL},
		{"0x100",	16,	0x100ULL},
		{"0x101",	16,	0x101ULL},
		{"0x7fff",	16,	0x7fffULL},
		{"0x8000",	16,	0x8000ULL},
		{"0x8001",	16,	0x8001ULL},
		{"0xffff",	16,	0xffffULL},
		{"0x10000",	16,	0x10000ULL},
		{"0x10001",	16,	0x10001ULL},
		{"0x7fffffff",	16,	0x7fffffffULL},
		{"0x80000000",	16,	0x80000000ULL},
		{"0x80000001",	16,	0x80000001ULL},
		{"0xffffffff",	16,	0xffffffffULL},
		{"0x100000000",	16,	0x100000000ULL},
		{"0x100000001",	16,	0x100000001ULL},
		{"0x7fffffffffffffff",	16,	0x7fffffffffffffffULL},
		{"0x8000000000000000",	16,	0x8000000000000000ULL},
		{"0x8000000000000001",	16,	0x8000000000000001ULL},
		{"0xfffffffffffffffe",	16,	0xfffffffffffffffeULL},
		{"0xffffffffffffffff",	16,	0xffffffffffffffffULL},

		{"0\n",	0,	0ULL},
	};
	TEST_OK(kstrtoull, unsigned long long, "%llu", test_ull_ok);
}

static void __init test_kstrtoull_fail(void)
{
	static DEFINE_TEST_FAIL(test_ull_fail) = {
		{"",	0},
		{"",	8},
		{"",	10},
		{"",	16},
		{"\n",	0},
		{"\n",	8},
		{"\n",	10},
		{"\n",	16},
		{"\n0",	0},
		{"\n0",	8},
		{"\n0",	10},
		{"\n0",	16},
		{"+",	0},
		{"+",	8},
		{"+",	10},
		{"+",	16},
		{"-",	0},
		{"-",	8},
		{"-",	10},
		{"-",	16},
		{"0x",	0},
		{"0x",	16},
		{"0X",	0},
		{"0X",	16},
		{"0 ",	0},
		{"1+",	0},
		{"1-",	0},
		{" 2",	0},
		
		{"0x0z",	0},
		{"0z",		0},
		{"a",		0},
		
		{"2",	2},
		{"8",	8},
		{"a",	10},
		{"A",	10},
		{"g",	16},
		{"G",	16},
		
		{"10000000000000000000000000000000000000000000000000000000000000000",	2},
		{"2000000000000000000000",	8},
		{"18446744073709551616",	10},
		{"10000000000000000",	16},
		
		{"-0", 0},
		{"-0", 8},
		{"-0", 10},
		{"-0", 16},
		{"-1", 0},
		{"-1", 8},
		{"-1", 10},
		{"-1", 16},
		
		{"-+1", 0},
		{"-+1", 8},
		{"-+1", 10},
		{"-+1", 16},
		
		{"0\n0", 0},
		{"0\n0", 8},
		{"0\n0", 10},
		{"0\n0", 16},
		{"0\n+", 0},
		{"0\n+", 8},
		{"0\n+", 10},
		{"0\n+", 16},
		{"0\n-", 0},
		{"0\n-", 8},
		{"0\n-", 10},
		{"0\n-", 16},
		{"0\n ", 0},
		{"0\n ", 8},
		{"0\n ", 10},
		{"0\n ", 16},
	};
	TEST_FAIL(kstrtoull, unsigned long long, "%llu", test_ull_fail);
}

static void __init test_kstrtoll_ok(void)
{
	DECLARE_TEST_OK(long long, struct test_ll);
	static DEFINE_TEST_OK(struct test_ll, test_ll_ok) = {
		{"0",	10,	0LL},
		{"1",	10,	1LL},
		{"127",	10,	127LL},
		{"128",	10,	128LL},
		{"129",	10,	129LL},
		{"255",	10,	255LL},
		{"256",	10,	256LL},
		{"257",	10,	257LL},
		{"32767",	10,	32767LL},
		{"32768",	10,	32768LL},
		{"32769",	10,	32769LL},
		{"65535",	10,	65535LL},
		{"65536",	10,	65536LL},
		{"65537",	10,	65537LL},
		{"2147483647",	10,	2147483647LL},
		{"2147483648",	10,	2147483648LL},
		{"2147483649",	10,	2147483649LL},
		{"4294967295",	10,	4294967295LL},
		{"4294967296",	10,	4294967296LL},
		{"4294967297",	10,	4294967297LL},
		{"9223372036854775807",	10,	9223372036854775807LL},

		{"-1",	10,	-1LL},
		{"-2",	10,	-2LL},
		{"-9223372036854775808",	10,	LLONG_MIN},
	};
	TEST_OK(kstrtoll, long long, "%lld", test_ll_ok);
}

static void __init test_kstrtoll_fail(void)
{
	static DEFINE_TEST_FAIL(test_ll_fail) = {
		{"9223372036854775808",	10},
		{"9223372036854775809",	10},
		{"18446744073709551614",	10},
		{"18446744073709551615",	10},
		{"-9223372036854775809",	10},
		{"-18446744073709551614",	10},
		{"-18446744073709551615",	10},
		
		{"-0",	0},
		{"-0",	8},
		{"-0",	10},
		{"-0",	16},
		
		{"-+1", 0},
		{"-+1", 8},
		{"-+1", 10},
		{"-+1", 16},
	};
	TEST_FAIL(kstrtoll, long long, "%lld", test_ll_fail);
}

static void __init test_kstrtou64_ok(void)
{
	DECLARE_TEST_OK(u64, struct test_u64);
	static DEFINE_TEST_OK(struct test_u64, test_u64_ok) = {
		{"0",	10,	0},
		{"1",	10,	1},
		{"126",	10,	126},
		{"127",	10,	127},
		{"128",	10,	128},
		{"129",	10,	129},
		{"254",	10,	254},
		{"255",	10,	255},
		{"256",	10,	256},
		{"257",	10,	257},
		{"32766",	10,	32766},
		{"32767",	10,	32767},
		{"32768",	10,	32768},
		{"32769",	10,	32769},
		{"65534",	10,	65534},
		{"65535",	10,	65535},
		{"65536",	10,	65536},
		{"65537",	10,	65537},
		{"2147483646",	10,	2147483646},
		{"2147483647",	10,	2147483647},
		{"2147483648",	10,	2147483648ULL},
		{"2147483649",	10,	2147483649ULL},
		{"4294967294",	10,	4294967294ULL},
		{"4294967295",	10,	4294967295ULL},
		{"4294967296",	10,	4294967296ULL},
		{"4294967297",	10,	4294967297ULL},
		{"9223372036854775806",	10,	9223372036854775806ULL},
		{"9223372036854775807",	10,	9223372036854775807ULL},
		{"9223372036854775808",	10,	9223372036854775808ULL},
		{"9223372036854775809",	10,	9223372036854775809ULL},
		{"18446744073709551614",	10,	18446744073709551614ULL},
		{"18446744073709551615",	10,	18446744073709551615ULL},
	};
	TEST_OK(kstrtou64, u64, "%llu", test_u64_ok);
}

static void __init test_kstrtou64_fail(void)
{
	static DEFINE_TEST_FAIL(test_u64_fail) = {
		{"-2",	10},
		{"-1",	10},
		{"18446744073709551616",	10},
		{"18446744073709551617",	10},
	};
	TEST_FAIL(kstrtou64, u64, "%llu", test_u64_fail);
}

static void __init test_kstrtos64_ok(void)
{
	DECLARE_TEST_OK(s64, struct test_s64);
	static DEFINE_TEST_OK(struct test_s64, test_s64_ok) = {
		{"-128",	10,	-128},
		{"-127",	10,	-127},
		{"-1",	10,	-1},
		{"0",	10,	0},
		{"1",	10,	1},
		{"126",	10,	126},
		{"127",	10,	127},
		{"128",	10,	128},
		{"129",	10,	129},
		{"254",	10,	254},
		{"255",	10,	255},
		{"256",	10,	256},
		{"257",	10,	257},
		{"32766",	10,	32766},
		{"32767",	10,	32767},
		{"32768",	10,	32768},
		{"32769",	10,	32769},
		{"65534",	10,	65534},
		{"65535",	10,	65535},
		{"65536",	10,	65536},
		{"65537",	10,	65537},
		{"2147483646",	10,	2147483646},
		{"2147483647",	10,	2147483647},
		{"2147483648",	10,	2147483648LL},
		{"2147483649",	10,	2147483649LL},
		{"4294967294",	10,	4294967294LL},
		{"4294967295",	10,	4294967295LL},
		{"4294967296",	10,	4294967296LL},
		{"4294967297",	10,	4294967297LL},
		{"9223372036854775806",	10,	9223372036854775806LL},
		{"9223372036854775807",	10,	9223372036854775807LL},
	};
	TEST_OK(kstrtos64, s64, "%lld", test_s64_ok);
}

static void __init test_kstrtos64_fail(void)
{
	static DEFINE_TEST_FAIL(test_s64_fail) = {
		{"9223372036854775808",	10},
		{"9223372036854775809",	10},
		{"18446744073709551614",	10},
		{"18446744073709551615",	10},
		{"18446744073709551616",	10},
		{"18446744073709551617",	10},
	};
	TEST_FAIL(kstrtos64, s64, "%lld", test_s64_fail);
}

static void __init test_kstrtou32_ok(void)
{
	DECLARE_TEST_OK(u32, struct test_u32);
	static DEFINE_TEST_OK(struct test_u32, test_u32_ok) = {
		{"0",	10,	0},
		{"1",	10,	1},
		{"126",	10,	126},
		{"127",	10,	127},
		{"128",	10,	128},
		{"129",	10,	129},
		{"254",	10,	254},
		{"255",	10,	255},
		{"256",	10,	256},
		{"257",	10,	257},
		{"32766",	10,	32766},
		{"32767",	10,	32767},
		{"32768",	10,	32768},
		{"32769",	10,	32769},
		{"65534",	10,	65534},
		{"65535",	10,	65535},
		{"65536",	10,	65536},
		{"65537",	10,	65537},
		{"2147483646",	10,	2147483646},
		{"2147483647",	10,	2147483647},
		{"2147483648",	10,	2147483648U},
		{"2147483649",	10,	2147483649U},
		{"4294967294",	10,	4294967294U},
		{"4294967295",	10,	4294967295U},
	};
	TEST_OK(kstrtou32, u32, "%u", test_u32_ok);
}

static void __init test_kstrtou32_fail(void)
{
	static DEFINE_TEST_FAIL(test_u32_fail) = {
		{"-2",	10},
		{"-1",	10},
		{"4294967296",	10},
		{"4294967297",	10},
		{"9223372036854775806",	10},
		{"9223372036854775807",	10},
		{"9223372036854775808",	10},
		{"9223372036854775809",	10},
		{"18446744073709551614",	10},
		{"18446744073709551615",	10},
		{"18446744073709551616",	10},
		{"18446744073709551617",	10},
	};
	TEST_FAIL(kstrtou32, u32, "%u", test_u32_fail);
}

static void __init test_kstrtos32_ok(void)
{
	DECLARE_TEST_OK(s32, struct test_s32);
	static DEFINE_TEST_OK(struct test_s32, test_s32_ok) = {
		{"-128",	10,	-128},
		{"-127",	10,	-127},
		{"-1",	10,	-1},
		{"0",	10,	0},
		{"1",	10,	1},
		{"126",	10,	126},
		{"127",	10,	127},
		{"128",	10,	128},
		{"129",	10,	129},
		{"254",	10,	254},
		{"255",	10,	255},
		{"256",	10,	256},
		{"257",	10,	257},
		{"32766",	10,	32766},
		{"32767",	10,	32767},
		{"32768",	10,	32768},
		{"32769",	10,	32769},
		{"65534",	10,	65534},
		{"65535",	10,	65535},
		{"65536",	10,	65536},
		{"65537",	10,	65537},
		{"2147483646",	10,	2147483646},
		{"2147483647",	10,	2147483647},
	};
	TEST_OK(kstrtos32, s32, "%d", test_s32_ok);
}

static void __init test_kstrtos32_fail(void)
{
	static DEFINE_TEST_FAIL(test_s32_fail) = {
		{"2147483648",	10},
		{"2147483649",	10},
		{"4294967294",	10},
		{"4294967295",	10},
		{"4294967296",	10},
		{"4294967297",	10},
		{"9223372036854775806",	10},
		{"9223372036854775807",	10},
		{"9223372036854775808",	10},
		{"9223372036854775809",	10},
		{"18446744073709551614",	10},
		{"18446744073709551615",	10},
		{"18446744073709551616",	10},
		{"18446744073709551617",	10},
	};
	TEST_FAIL(kstrtos32, s32, "%d", test_s32_fail);
}

static void __init test_kstrtou16_ok(void)
{
	DECLARE_TEST_OK(u16, struct test_u16);
	static DEFINE_TEST_OK(struct test_u16, test_u16_ok) = {
		{"0",	10,	0},
		{"1",	10,	1},
		{"126",	10,	126},
		{"127",	10,	127},
		{"128",	10,	128},
		{"129",	10,	129},
		{"254",	10,	254},
		{"255",	10,	255},
		{"256",	10,	256},
		{"257",	10,	257},
		{"32766",	10,	32766},
		{"32767",	10,	32767},
		{"32768",	10,	32768},
		{"32769",	10,	32769},
		{"65534",	10,	65534},
		{"65535",	10,	65535},
	};
	TEST_OK(kstrtou16, u16, "%hu", test_u16_ok);
}

static void __init test_kstrtou16_fail(void)
{
	static DEFINE_TEST_FAIL(test_u16_fail) = {
		{"-2",	10},
		{"-1",	10},
		{"65536",	10},
		{"65537",	10},
		{"2147483646",	10},
		{"2147483647",	10},
		{"2147483648",	10},
		{"2147483649",	10},
		{"4294967294",	10},
		{"4294967295",	10},
		{"4294967296",	10},
		{"4294967297",	10},
		{"9223372036854775806",	10},
		{"9223372036854775807",	10},
		{"9223372036854775808",	10},
		{"9223372036854775809",	10},
		{"18446744073709551614",	10},
		{"18446744073709551615",	10},
		{"18446744073709551616",	10},
		{"18446744073709551617",	10},
	};
	TEST_FAIL(kstrtou16, u16, "%hu", test_u16_fail);
}

static void __init test_kstrtos16_ok(void)
{
	DECLARE_TEST_OK(s16, struct test_s16);
	static DEFINE_TEST_OK(struct test_s16, test_s16_ok) = {
		{"-130",	10,	-130},
		{"-129",	10,	-129},
		{"-128",	10,	-128},
		{"-127",	10,	-127},
		{"-1",	10,	-1},
		{"0",	10,	0},
		{"1",	10,	1},
		{"126",	10,	126},
		{"127",	10,	127},
		{"128",	10,	128},
		{"129",	10,	129},
		{"254",	10,	254},
		{"255",	10,	255},
		{"256",	10,	256},
		{"257",	10,	257},
		{"32766",	10,	32766},
		{"32767",	10,	32767},
	};
	TEST_OK(kstrtos16, s16, "%hd", test_s16_ok);
}

static void __init test_kstrtos16_fail(void)
{
	static DEFINE_TEST_FAIL(test_s16_fail) = {
		{"32768",	10},
		{"32769",	10},
		{"65534",	10},
		{"65535",	10},
		{"65536",	10},
		{"65537",	10},
		{"2147483646",	10},
		{"2147483647",	10},
		{"2147483648",	10},
		{"2147483649",	10},
		{"4294967294",	10},
		{"4294967295",	10},
		{"4294967296",	10},
		{"4294967297",	10},
		{"9223372036854775806",	10},
		{"9223372036854775807",	10},
		{"9223372036854775808",	10},
		{"9223372036854775809",	10},
		{"18446744073709551614",	10},
		{"18446744073709551615",	10},
		{"18446744073709551616",	10},
		{"18446744073709551617",	10},
	};
	TEST_FAIL(kstrtos16, s16, "%hd", test_s16_fail);
}

static void __init test_kstrtou8_ok(void)
{
	DECLARE_TEST_OK(u8, struct test_u8);
	static DEFINE_TEST_OK(struct test_u8, test_u8_ok) = {
		{"0",	10,	0},
		{"1",	10,	1},
		{"126",	10,	126},
		{"127",	10,	127},
		{"128",	10,	128},
		{"129",	10,	129},
		{"254",	10,	254},
		{"255",	10,	255},
	};
	TEST_OK(kstrtou8, u8, "%hhu", test_u8_ok);
}

static void __init test_kstrtou8_fail(void)
{
	static DEFINE_TEST_FAIL(test_u8_fail) = {
		{"-2",	10},
		{"-1",	10},
		{"256",	10},
		{"257",	10},
		{"32766",	10},
		{"32767",	10},
		{"32768",	10},
		{"32769",	10},
		{"65534",	10},
		{"65535",	10},
		{"65536",	10},
		{"65537",	10},
		{"2147483646",	10},
		{"2147483647",	10},
		{"2147483648",	10},
		{"2147483649",	10},
		{"4294967294",	10},
		{"4294967295",	10},
		{"4294967296",	10},
		{"4294967297",	10},
		{"9223372036854775806",	10},
		{"9223372036854775807",	10},
		{"9223372036854775808",	10},
		{"9223372036854775809",	10},
		{"18446744073709551614",	10},
		{"18446744073709551615",	10},
		{"18446744073709551616",	10},
		{"18446744073709551617",	10},
	};
	TEST_FAIL(kstrtou8, u8, "%hhu", test_u8_fail);
}

static void __init test_kstrtos8_ok(void)
{
	DECLARE_TEST_OK(s8, struct test_s8);
	static DEFINE_TEST_OK(struct test_s8, test_s8_ok) = {
		{"-128",	10,	-128},
		{"-127",	10,	-127},
		{"-1",	10,	-1},
		{"0",	10,	0},
		{"1",	10,	1},
		{"126",	10,	126},
		{"127",	10,	127},
	};
	TEST_OK(kstrtos8, s8, "%hhd", test_s8_ok);
}

static void __init test_kstrtos8_fail(void)
{
	static DEFINE_TEST_FAIL(test_s8_fail) = {
		{"-130",	10},
		{"-129",	10},
		{"128",	10},
		{"129",	10},
		{"254",	10},
		{"255",	10},
		{"256",	10},
		{"257",	10},
		{"32766",	10},
		{"32767",	10},
		{"32768",	10},
		{"32769",	10},
		{"65534",	10},
		{"65535",	10},
		{"65536",	10},
		{"65537",	10},
		{"2147483646",	10},
		{"2147483647",	10},
		{"2147483648",	10},
		{"2147483649",	10},
		{"4294967294",	10},
		{"4294967295",	10},
		{"4294967296",	10},
		{"4294967297",	10},
		{"9223372036854775806",	10},
		{"9223372036854775807",	10},
		{"9223372036854775808",	10},
		{"9223372036854775809",	10},
		{"18446744073709551614",	10},
		{"18446744073709551615",	10},
		{"18446744073709551616",	10},
		{"18446744073709551617",	10},
	};
	TEST_FAIL(kstrtos8, s8, "%hhd", test_s8_fail);
}

static int __init test_kstrtox_init(void)
{
	test_kstrtoull_ok();
	test_kstrtoull_fail();
	test_kstrtoll_ok();
	test_kstrtoll_fail();

	test_kstrtou64_ok();
	test_kstrtou64_fail();
	test_kstrtos64_ok();
	test_kstrtos64_fail();

	test_kstrtou32_ok();
	test_kstrtou32_fail();
	test_kstrtos32_ok();
	test_kstrtos32_fail();

	test_kstrtou16_ok();
	test_kstrtou16_fail();
	test_kstrtos16_ok();
	test_kstrtos16_fail();

	test_kstrtou8_ok();
	test_kstrtou8_fail();
	test_kstrtos8_ok();
	test_kstrtos8_fail();
	return -EINVAL;
}
module_init(test_kstrtox_init);
MODULE_LICENSE("Dual BSD/GPL");
