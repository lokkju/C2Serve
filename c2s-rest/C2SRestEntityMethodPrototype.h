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

#ifndef C2SRESTENTITYMETHODPROTOTYPE_H_
#define C2SRESTENTITYMETHODPROTOTYPE_H_

#include "C2SRestMethodPrototype.h"
#include "C2SRestEntityStreamer.h"
#include "C2SHttpInvalidEntityType.h"

#include <cassert>

namespace c2s
{

  template <class EntityType>
  class C2SRestEntityMethodPrototype : public C2SRestMethodPrototype
  {
  public:

    virtual ~C2SRestEntityMethodPrototype();

    virtual C2SHttpResponse *processRequest( const C2SHttpRequest &request );

  protected:

    C2SRestEntityMethodPrototype( C2SHttpMethod methodType , const std::string &sPath );

    void installEntityStreamer( C2SRestEntityStreamer<EntityType> *pEntityStreamer );

    C2SHttpResponse *buildResponse( C2SHttpStatus status , const EntityType &data ) const;

  private:

    const C2SRestEntityStreamer<EntityType> *detectEntityStreamerToUseForRequest( const C2SHttpRequest &request ) const;

    const C2SRestEntityStreamer<EntityType> *getFirstEntityStreamerAsDefault() const;

    typedef std::list<C2SRestEntityStreamer<EntityType>*> EntityStreamerList;

    const C2SRestEntityStreamer<EntityType> *m_pEntityStreamerToUseForNextResponse;

    std::map<std::string,C2SHttpMediaType> m_allowedEntityMediaTypes;

    EntityStreamerList m_entityStreamersByTimeOfRegistration;

  };

  template <class EntityType>
  C2SRestEntityMethodPrototype<EntityType>::C2SRestEntityMethodPrototype( C2SHttpMethod methodType , const std::string &sPath )
    : C2SRestMethodPrototype( methodType , sPath ),
      m_pEntityStreamerToUseForNextResponse( NULL )
  {};

  template <class EntityType>
  C2SRestEntityMethodPrototype<EntityType>::~C2SRestEntityMethodPrototype()
  {
    typename EntityStreamerList::iterator esit = m_entityStreamersByTimeOfRegistration.begin();
    typename EntityStreamerList::iterator esend = m_entityStreamersByTimeOfRegistration.end();
    for ( ; esit != esend; ++esit )
    {
      delete *esit;
    }
  }

  template <class EntityType>
  void C2SRestEntityMethodPrototype<EntityType>::installEntityStreamer( C2SRestEntityStreamer<EntityType> *pEntityStreamer )
  {
    const C2SHttpMediaType &mediatype = pEntityStreamer->getMediaType();

    if ( m_allowedEntityMediaTypes.find( mediatype.Type ) != m_allowedEntityMediaTypes.end() )
      throw C2SRestException( "C2SRestEntityMethodPrototype::installEntityStreamer: " , "Media type already exists: " + mediatype.Type , InternalServerError );

    m_allowedEntityMediaTypes.insert( std::make_pair( mediatype.Type , mediatype ) );
    m_entityStreamersByTimeOfRegistration.push_back( pEntityStreamer );
  }

  template <class EntityType>
  C2SHttpResponse *C2SRestEntityMethodPrototype<EntityType>::processRequest( const C2SHttpRequest &request )
  {
    m_pEntityStreamerToUseForNextResponse = this->detectEntityStreamerToUseForRequest( request );
    return C2SRestMethodPrototype::processRequest( request );
  }

  template <>
  inline C2SHttpResponse *C2SRestEntityMethodPrototype<C2SHttpInvalidEntityType>::processRequest( const C2SHttpRequest &request )
  {
    m_pEntityStreamerToUseForNextResponse = NULL;
    return C2SRestMethodPrototype::processRequest( request );
  }

  template <class EntityType>
  const C2SRestEntityStreamer<EntityType> *C2SRestEntityMethodPrototype<EntityType>::detectEntityStreamerToUseForRequest( const C2SHttpRequest &request ) const
  {
    if ( !m_entityStreamersByTimeOfRegistration.size() )
      throw C2SRestException( "C2SRestEntityMethodPrototype::detectEntityStreamerToUseForRequest: " , "No entity streamers available" , InternalServerError );

    typename EntityStreamerList::const_iterator esit = m_entityStreamersByTimeOfRegistration.begin();
    typename EntityStreamerList::const_iterator esend = m_entityStreamersByTimeOfRegistration.end();
    for ( ; esit != esend; ++esit )
    {
      const C2SRestEntityStreamer<EntityType> *pCurrentEntityStreamerObserved = *esit;
      if ( request.header().Fields.isAccept( pCurrentEntityStreamerObserved->getMediaType().Type ) )
        return pCurrentEntityStreamerObserved;
    }

    if ( request.header().Fields.isAccept( C2SHttpMediaType::wildcard ) )
      return this->getFirstEntityStreamerAsDefault();

    throw C2SRestException( "C2SRestEntityMethodPrototype::detectEntityStreamerToUseForRequest: " , "No appropriate content type was found" , NotAcceptable );
  }

  template <class EntityType>
  const C2SRestEntityStreamer<EntityType> *C2SRestEntityMethodPrototype<EntityType>::getFirstEntityStreamerAsDefault() const
  {
    return *( m_entityStreamersByTimeOfRegistration.begin() );
  }

  template <class EntityType>
  C2SHttpResponse *C2SRestEntityMethodPrototype<EntityType>::buildResponse( C2SHttpStatus status , const EntityType &data ) const
  {
    assert( m_pEntityStreamerToUseForNextResponse );
    C2SHttpResponse *pResponse = C2SHttpResponse::build( status );
    pResponse->setEntity( m_pEntityStreamerToUseForNextResponse->entity( data ) );
    pResponse->header().Fields.setContentType( m_pEntityStreamerToUseForNextResponse->getMediaType().Type );
    return pResponse;
  }

  template <>
  inline C2SHttpResponse *C2SRestEntityMethodPrototype<C2SHttpInvalidEntityType>::buildResponse( C2SHttpStatus status , const C2SHttpInvalidEntityType &data ) const
  {
    assert( m_pEntityStreamerToUseForNextResponse == NULL );
    throw C2SRestException( "C2SRestEntityMethodPrototype<C2SHttpInvalidEntityType>::buildResponse: " , "Response with entity body is not allowed for entity type C2SHttpInvalidEntityType" , InternalServerError );
  }

}

#endif /* C2SRESTENTITYMETHODPROTOTYPE_H_ */
