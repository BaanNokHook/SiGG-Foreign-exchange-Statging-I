/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "governance-votedb.h"

CGovernanceObjectVoteFile::CGovernanceObjectVoteFile()
    : nMemoryVotes(0),
      listVotes(),
      mapVoteIndex()
{
}

CGovernanceObjectVoteFile::CGovernanceObjectVoteFile(const CGovernanceObjectVoteFile& other)
    : nMemoryVotes(other.nMemoryVotes),
      listVotes(other.listVotes),
      mapVoteIndex()
{
    RebuildIndex();
}

void CGovernanceObjectVoteFile::AddVote(const CGovernanceVote& vote)
{
    uint256 nHash = vote.GetHash();
    // make sure to never add/update already known votes
    if (HasVote(nHash))
        return;
    listVotes.push_front(vote);
    mapVoteIndex.emplace(nHash, listVotes.begin());
    ++nMemoryVotes;
}

bool CGovernanceObjectVoteFile::HasVote(const uint256& nHash) const
{
    return mapVoteIndex.find(nHash) != mapVoteIndex.end();
}

bool CGovernanceObjectVoteFile::SerializeVoteToStream(const uint256& nHash, CDataStream& ss) const
{
    vote_m_cit it = mapVoteIndex.find(nHash);
    if (it == mapVoteIndex.end()) {
        return false;
    }
    ss << *(it->second);
    return true;
}

std::vector<CGovernanceVote> CGovernanceObjectVoteFile::GetVotes() const
{
    std::vector<CGovernanceVote> vecResult;
    for (vote_l_cit it = listVotes.begin(); it != listVotes.end(); ++it) {
        vecResult.push_back(*it);
    }
    return vecResult;
}

void CGovernanceObjectVoteFile::RemoveVotesFromDynode(const COutPoint& outpointDynode)
{
    vote_l_it it = listVotes.begin();
    while (it != listVotes.end()) {
        if (it->GetDynodeOutpoint() == outpointDynode) {
            --nMemoryVotes;
            mapVoteIndex.erase(it->GetHash());
            listVotes.erase(it++);
        } else {
            ++it;
        }
    }
}

void CGovernanceObjectVoteFile::RebuildIndex()
{
    mapVoteIndex.clear();
    nMemoryVotes = 0;
    vote_l_it it = listVotes.begin();
    while (it != listVotes.end()) {
        CGovernanceVote& vote = *it;
        uint256 nHash = vote.GetHash();
        if (mapVoteIndex.find(nHash) == mapVoteIndex.end()) {
            mapVoteIndex[nHash] = it;
            ++nMemoryVotes;
            ++it;
        } else {
            listVotes.erase(it++);
        }
    }
}