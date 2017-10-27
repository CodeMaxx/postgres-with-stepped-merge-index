/*-------------------------------------------------------------------------
 *
 * smerge.c
 *	  Implementation of Lehman and Yao's btree management algorithm for
 *	  Postgres.
 *
 * NOTES
 *	  This file contains only the public interface routines.
 *
 *
 * Portions Copyright (c) 1996-2016, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * IDENTIFICATION
 *	  src/backend/access/smerge/smerge.c
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"

#include "access/smerge.h"
#include "access/relscan.h"
#include "access/xlog.h"
#include "catalog/index.h"
#include "commands/vacuum.h"
#include "storage/indexfsm.h"
#include "storage/ipc.h"
#include "storage/lmgr.h"
#include "storage/smgr.h"
#include "tcop/tcopprot.h"		/* pgrminclude ignore */
#include "utils/index_selfuncs.h"
#include "utils/memutils.h"

/*
 * Btree handler function: return IndexAmRoutine with access method parameters
 * and callbacks.
 */
Datum
smergehandler(PG_FUNCTION_ARGS)
{
	IndexAmRoutine *amroutine = makeNode(IndexAmRoutine);

	amroutine->amstrategies = 0;
	amroutine->amsupport = 0;
	amroutine->amcanorder = false;
	amroutine->amcanorderbyop = false;
	amroutine->amcanbackward = false;
	amroutine->amcanunique = true;
	amroutine->amcanmulticol = false;
	amroutine->amoptionalkey = true;
	amroutine->amsearcharray = false;
	amroutine->amsearchnulls = false;
	amroutine->amstorage = false;
	amroutine->amclusterable = false;
	amroutine->ampredlocks = false;
	amroutine->amkeytype = InvalidOid;

	amroutine->ambuild = smergebuild;
	amroutine->ambuildempty = smergebuildempty;
	amroutine->aminsert = smergeinsert;
	amroutine->ambulkdelete = smergebulkdelete;
	amroutine->amvacuumcleanup = smergevacuumcleanup;
	amroutine->amcanreturn = smergecanreturn;
	amroutine->amcostestimate = smergecostestimate;
	amroutine->amoptions = NULL;
	amroutine->amproperty = NULL;
	amroutine->amvalidate = NULL;
	amroutine->ambeginscan = smergebeginscan;
	amroutine->amrescan = smergerescan;
	amroutine->amgettuple = smergegettuple;
	amroutine->amgetbitmap = NULL;
	amroutine->amendscan = smergeendscan;
	amroutine->ammarkpos = NULL;
	amroutine->amrestrpos = NULL;

	PG_RETURN_POINTER(amroutine);
}

/*
 *	btbuild() -- build a new btree index.
 */
IndexBuildResult *
smergebuild(Relation heap, Relation index, IndexInfo *indexInfo)
{}


/*
 *	btbuildempty() -- build an empty btree index in the initialization fork
 */
void
smergebuildempty(Relation index)
{}

/*
 *	btinsert() -- insert an index tuple into a btree.
 *
 *		Descend the tree recursively, find the appropriate location for our
 *		new tuple, and put it there.
 */
bool
smergeinsert(Relation rel, Datum *values, bool *isnull,
		 ItemPointer ht_ctid, Relation heapRel,
		 IndexUniqueCheck checkUnique)
{}

/*
 *	btgettuple() -- Get the next tuple in the scan.
 */
bool
smergegettuple(IndexScanDesc scan, ScanDirection dir)
{}

/*
 *	btbeginscan() -- start a scan on a btree index
 */
IndexScanDesc
smergebeginscan(Relation rel, int nkeys, int norderbys)
{}

/*
 *	btrescan() -- rescan an index relation
 */
void
smergerescan(IndexScanDesc scan, ScanKey scankey, int nscankeys,
		 ScanKey orderbys, int norderbys)
{}

/*
 *	btendscan() -- close down a scan
 */
void
smergeendscan(IndexScanDesc scan)
{}

/*
 * Bulk deletion of all index entries pointing to a set of heap tuples.
 * The set of target tuples is specified via a callback routine that tells
 * whether any given heap tuple (identified by ItemPointer) is being deleted.
 *
 * Result: a palloc'd struct containing statistical info for VACUUM displays.
 */
IndexBulkDeleteResult *
smergebulkdelete(IndexVacuumInfo *info, IndexBulkDeleteResult *stats,
			 IndexBulkDeleteCallback callback, void *callback_state)
{}

/*
 * Post-VACUUM cleanup.
 *
 * Result: a palloc'd struct containing statistical info for VACUUM displays.
 */
IndexBulkDeleteResult *
smergevacuumcleanup(IndexVacuumInfo *info, IndexBulkDeleteResult *stats)
{}

/*
 *	btcanreturn() -- Check whether btree indexes support index-only scans.
 *
 * btrees always do, so this is trivial.
 */
bool
smergecanreturn(Relation index, int attno)
{
	return true;
}

void
smergecostestimate()
{

}
