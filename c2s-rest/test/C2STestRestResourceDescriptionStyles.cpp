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

#include "C2STestRestResourceDescriptionStyles.h"

#include "C2SRestResourceDescriptionException.h"

#include <boost/test/unit_test.hpp>

namespace c2s
{

  namespace test
  {

    C2STestRestResourceDescriptionStyles::C2STestRestResourceDescriptionStyles()
    {
    }

    C2STestRestResourceDescriptionStyles::~C2STestRestResourceDescriptionStyles()
    {
    }

    void C2STestRestResourceDescriptionStyles::runTest()
    {
      C2STestRestResourceDescriptionStyles testRestResourceDescriptionStyles;
      testRestResourceDescriptionStyles.createAndCheckStylesForHTMLElementDiv();
      testRestResourceDescriptionStyles.createAndCheckStylesForHTMLElementDivClassCode();
      testRestResourceDescriptionStyles.checkStringCreatedForStyles();
    }

    void C2STestRestResourceDescriptionStyles::createAndCheckStylesForHTMLElementDiv()
    {
      C2SRestResourceDescriptionStylesClass stylesForHTMLElement( "div" );
      stylesForHTMLElement.addStyle( "background-color" , "#eee" );
      BOOST_CHECK_THROW( stylesForHTMLElement.addStyle( "background-color" , "#eee" ) , C2SRestResourceDescriptionException );
      stylesForHTMLElement.addStyle( "text-align" , "center" );
      m_listOfStylesForHTMLElements.addStylesForCSSClass( stylesForHTMLElement );
      BOOST_CHECK_THROW( m_listOfStylesForHTMLElements.addStylesForCSSClass( stylesForHTMLElement ) , C2SRestResourceDescriptionException );
      std::string sCSSStringCreatedFromStyles = stylesForHTMLElement.toCSSStringWithIndentAsSpaces( 4 );
      std::string sCSSStringExpectedFromStyles = "    div\n    {\n      background-color: #eee;\n      text-align: center;\n    }";
      BOOST_CHECK( sCSSStringCreatedFromStyles == sCSSStringExpectedFromStyles );
    }

    void C2STestRestResourceDescriptionStyles::createAndCheckStylesForHTMLElementDivClassCode()
    {
      C2SRestResourceDescriptionStylesClass stylesForHTMLElement( "div.code" );
      stylesForHTMLElement.addStyle( "background-color" , "#aaa" );
      stylesForHTMLElement.addStyle( "font-size" , "8pt" );
      stylesForHTMLElement.addStyle( "margin" , "0px auto" );
      std::string sCSSStringCreatedFromStyles = stylesForHTMLElement.toCSSStringWithIndentAsSpaces( 2 );
      std::string sCSSStringExpectedFromStyles = "  div.code\n  {\n    background-color: #aaa;\n    font-size: 8pt;\n    margin: 0px auto;\n  }";
      BOOST_CHECK( sCSSStringCreatedFromStyles == sCSSStringExpectedFromStyles );
      m_listOfStylesForHTMLElements.addStylesForCSSClass( stylesForHTMLElement );
    }

    void C2STestRestResourceDescriptionStyles::checkStringCreatedForStyles() const
    {
      std::string sCSSStringCreatedFromStyles = m_listOfStylesForHTMLElements.toCSSStringWithIndentAsSpaces( 2 );
      std::string sCSSStringExpectedFromStyles = "  div\n  {\n    background-color: #eee;\n    text-align: center;\n  }\n\n  div.code\n  {\n    background-color: #aaa;\n    font-size: 8pt;\n    margin: 0px auto;\n  }\n\n";
      BOOST_CHECK( sCSSStringCreatedFromStyles == sCSSStringExpectedFromStyles );
    }

  }

}
