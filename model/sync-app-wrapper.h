/* -*- Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2012 University of California, Los Angeles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Zhenkai Zhu <zhenkai@cs.ucla.edu>
 *         卞超轶 Chaoyi Bian <bcy@pku.edu.cn>
 *	   Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 */

#ifndef SYNC_LEAF_H
#define SYNC_LEAF_H
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include "sync-ccnx-wrapper.h"
#include "sync-interest-table.h"
#include "sync-data-buffer.h"
#include "sync-diff-state.h"
#include "sync-full-state.h"

namespace Sync {

/**
 * \ingroup sync
 * @brief A wrapper for SyncApp, which handles ccnx related things (process
 * interests and data)
 */
class SyncAppWrapper
{
public:
	/**
	 * @brief constructor for this class; 
	 * @param syncPrefix the name prefix to use for the Sync Interest
	 * @param fetch the fetch function, which will be called to actually fetch
	 * the app data when new remote names are learned
	 */
	SyncAppWrapper(std::string syncPrefix, boost::function<void (string, long,
	long)> fetch);

	~SyncAppWrapper();
	/**
	 * a wrapper for the same func in SyncApp
	 */
	void addLocalNames(std::string prefix, long seq);

	/**
	 * @brief respond to the Sync Interest; a lot of logic needs to go in here
	 * @param interest the Sync Interest in string format
	 */
	void respondSyncInterest(std::string interest);	

	/**
	 * @brief process the fetched sync data
	 * @param dataBuffer the sync data
	 */
	void processSyncData(boost::shared_ptr<DataBuffer> dataBuffer);

private:
	sendSyncInterest();

private:
	boost::shared_ptr<CcnxWrapper> m_ccnxHandle;
	boost::shared_ptr<SyncApp> m_syncApp;
	boost::function<void (string, long, long)> m_fetch;
	SyncInterestTable m_syncInterestTable;	
	std::string m_syncPrefix;
};


} // Sync

#endif // SYNC_LEAF_H