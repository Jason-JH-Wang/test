/*-------------------------------------------------------------------------
 *
 * kwlookup.h
 *	  Key word lookup for PostgreSQL
 *
 *
 * Portions Copyright (c) 1996-2022, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/common/kwlookup.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef KWLOOKUP_H
#define KWLOOKUP_H

/* Hash function used by ScanKeywordLookup */
typedef int (*ScanKeywordHashFunc) (const void *key, size_t keylen);

/*
 * This struct contains the data needed by ScanKeywordLookup to perform a
 * search within a set of keywords.  The contents are typically generated by
 * src/tools/gen_keywordlist.pl from a header containing PG_KEYWORD macros.
 */
typedef struct ScanKeywordList
{
	const char *kw_string;		/* all keywords in order, separated by \0 */
	const uint16 *kw_offsets;	/* offsets to the start of each keyword */
	ScanKeywordHashFunc hash;	/* perfect hash function for keywords */
	int			num_keywords;	/* number of keywords */
	int			max_kw_len;		/* length of longest keyword */
} ScanKeywordList;


extern int	ScanKeywordLookup(const char *str, const ScanKeywordList *keywords);

/* Code that wants to retrieve the text of the N'th keyword should use this. */
static inline const char *
GetScanKeyword(int n, const ScanKeywordList *keywords)
{
	return keywords->kw_string + keywords->kw_offsets[n];
}

#endif							/* KWLOOKUP_H */
