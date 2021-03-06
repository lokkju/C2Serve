/**

	Copyright (c) 2011, C2Serve (http://www.c2serve.eu)
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	1. Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.
	3. All advertising materials mentioning features or use of this software
	   must display the following acknowledgement: "This product includes software of the C2Serve project".
	4. Neither the name of the C2Serve project nor the
	   names of its contributors may be used to endorse or promote products
	   derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY C2SERVE ''AS IS'' AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL C2SERVE BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#include "C2SRestPathSegmentList.h"
#include "C2SRestException.h"

#include <iostream>
#include <cassert>

namespace c2s
{

  C2SRestPathSegmentList::C2SRestPathSegmentList()
  {
  }

  C2SRestPathSegmentList::~C2SRestPathSegmentList()
  {
    iterator it = m_pathSegments.begin();
    for ( ; it != m_pathSegments.end(); ++it )
      delete *it;
  }

  void C2SRestPathSegmentList::appendPathSegment( C2SRestPathSegment *pSegment )
  {
    m_pathSegments.push_back( pSegment );
  }

  int C2SRestPathSegmentList::getDistanceToPathIDs( const C2SRestPathIDList &pathList ) const
  {
    //URI is too long
    if ( pathList.size() > m_pathSegments.size() )
      return -1;

    const_iterator it = m_pathSegments.begin();
    const_iterator end = m_pathSegments.end();

    int iDistance = 0;
    int iDistanceStatus = 0;

    for ( unsigned int iPathSegmentIdx = 0; it != end; ++it, ++iPathSegmentIdx )
    {
      //URI is too short
      if ( iPathSegmentIdx == pathList.size() )
        return -1;

      const std::string &sPathSegmentID = pathList[ iPathSegmentIdx ];
      const C2SRestPathSegment &segment = *( *it );

      //segment missmatch
      if ( !segment.isValidPathID( sPathSegmentID ) )
        return -1;

      C2SRestPathSegment::EPathSegmentType pathSegmentType = segment.getPathSegmentType();
      if ( pathSegmentType == C2SRestPathSegment::Parameter )
        iDistanceStatus += 1;

      iDistance += iDistanceStatus;
    }

    return iDistance;
  }

  void C2SRestPathSegmentList::processPathIDs( const C2SRestPathIDList &pathList )
  {
    iterator it = m_pathSegments.begin();
    iterator end = m_pathSegments.end();
    for ( unsigned int iPathSegmentIdx = 0; it != end; ++it, ++iPathSegmentIdx )
    {
      if ( iPathSegmentIdx == pathList.size() )
        throw C2SRestException( "C2SRestPathSegmentList::handle: " , "URI is too short!" , InternalServerError );

      const std::string &sPathID = pathList[ iPathSegmentIdx ];
      C2SRestPathSegment &segment = *( *it );
      segment.processPathID( sPathID );
    }
  }

  bool C2SRestPathSegmentList::operator==( const C2SRestPathSegmentList &pathSegmentsToCheck ) const
  {
    if ( m_pathSegments.size() != pathSegmentsToCheck.m_pathSegments.size() )
      return false;

    const_iterator itPathSegmentsTheir = pathSegmentsToCheck.m_pathSegments.begin();
    const_iterator itPathSegmentsThis = m_pathSegments.begin();
    const_iterator itPathSegmentsThisEnd = m_pathSegments.end();
    for ( ; itPathSegmentsThis != itPathSegmentsThisEnd; ++itPathSegmentsTheir , ++itPathSegmentsThis )
    {
      assert( itPathSegmentsTheir != pathSegmentsToCheck.m_pathSegments.end() );

      const C2SRestPathSegment &pathSegmentThis = *( *itPathSegmentsThis );
      const C2SRestPathSegment &pathSegmentTheir = *( *itPathSegmentsTheir );
      if ( pathSegmentThis != pathSegmentTheir )
        return false;
    }

    return true;
  }

}
