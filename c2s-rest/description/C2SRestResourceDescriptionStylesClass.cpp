/**

 Copyright (c) 2012, C2Serve (http://www.c2serve.eu)
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

#include "C2SRestResourceDescriptionStylesClass.h"
#include "C2SRestResourceDescriptionException.h"
#include "C2SRestResourceDescription.h"

#include "StringUtils.h"

namespace c2s
{

  C2SRestResourceDescriptionStylesClass::C2SRestResourceDescriptionStylesClass( const std::string &sCSSClassName )
    : m_sCSSClassName( sCSSClassName )
  {
  }

  C2SRestResourceDescriptionStylesClass::~C2SRestResourceDescriptionStylesClass()
  {
  }

  void C2SRestResourceDescriptionStylesClass::addStyle( const std::string &sCSSPropertyName , const std::string &sCSSPropertyValue )
  {
    if ( m_mapContainingStyles.find( sCSSPropertyName ) != m_mapContainingStyles.end() )
      throw C2SRestResourceDescriptionException( "C2SRestResourceDescriptionStylesClass::addStyle: " , "Duplicate CSS property for class " + m_sCSSClassName + ": " + sCSSPropertyName , InternalServerError );
    m_mapContainingStyles[ sCSSPropertyName ] = sCSSPropertyValue;
  }

  std::string C2SRestResourceDescriptionStylesClass::toCSSStringWithIndentAsSpaces( unsigned int iIndentInSpaces ) const
  {
    std::string sIndent = util::createIndentWithSpaces( iIndentInSpaces );
    std::string sCSSStylesAsString = sIndent + m_sCSSClassName + "\n";
    sCSSStylesAsString += sIndent + "{\n";
    sCSSStylesAsString += this->createStringFromStylesWithIndent( iIndentInSpaces + C2SRestResourceDescription::iIndentInSpaces );
    sCSSStylesAsString += sIndent + "}";
    return sCSSStylesAsString;
  }

  std::string C2SRestResourceDescriptionStylesClass::createStringFromStylesWithIndent( unsigned int iIndentInSpaces ) const
  {
    std::string sIndent = util::createIndentWithSpaces( iIndentInSpaces );
    std::string sStylesAsCSSString;
    std::map<std::string,std::string>::const_iterator it = m_mapContainingStyles.begin();
    std::map<std::string,std::string>::const_iterator end = m_mapContainingStyles.end();
    for ( ; it != end; ++it )
      sStylesAsCSSString += sIndent + it->first + ": " + it->second + ";\n";
    return sStylesAsCSSString;
  }

}
