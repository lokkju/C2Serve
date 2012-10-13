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

#include "C2SRestResourceAPIDocumentCreateDefaultStyles.h"

namespace c2s
{

  C2SRestResourceAPIDocumentCreateDefaultStyles::C2SRestResourceAPIDocumentCreateDefaultStyles()
  {
  }

  C2SRestResourceAPIDocumentCreateDefaultStyles::~C2SRestResourceAPIDocumentCreateDefaultStyles()
  {
  }

  C2SRestResourceAPIDocumentStylesList C2SRestResourceAPIDocumentCreateDefaultStyles::createDefaultStyles()
  {
    C2SRestResourceAPIDocumentCreateDefaultStyles createDefaultStyles;
    createDefaultStyles.createStyles();
    return createDefaultStyles.m_defaultListOfCSSStylesForResourceDescription;
  }

  void C2SRestResourceAPIDocumentCreateDefaultStyles::createStyles()
  {
    this->createStylesForBody();
    this->createStylesForDiv();
    this->createStylesForH1();
    this->createStylesForH2();
    this->createStylesForResourceBrief();
  }

  void C2SRestResourceAPIDocumentCreateDefaultStyles::createStylesForBody()
  {
    C2SRestResourceAPIDocumentStylesClass stylesClass( "body" );
    stylesClass.addStyle( "background-color" , "#eee" );
    stylesClass.addStyle( "text-align" , "center" );
    stylesClass.addStyle( "margin" , "0px auto" );
    stylesClass.addStyle( "color" , "#2D313D" );
    stylesClass.addStyle( "font-family" , "\"Gill Sans\", \"Trebuchet MS\", \"DejaVu Sans\"" );
    m_defaultListOfCSSStylesForResourceDescription.addStylesForCSSClass( stylesClass );
  }

  void C2SRestResourceAPIDocumentCreateDefaultStyles::createStylesForDiv()
  {
    C2SRestResourceAPIDocumentStylesClass stylesClass( "div" );
    stylesClass.addStyle( "width" , "1000px" );
    stylesClass.addStyle( "text-align" , "justify" );
    stylesClass.addStyle( "margin" , "0px auto" );
    m_defaultListOfCSSStylesForResourceDescription.addStylesForCSSClass( stylesClass );
  }

  void C2SRestResourceAPIDocumentCreateDefaultStyles::createStylesForH1()
  {
    C2SRestResourceAPIDocumentStylesClass stylesClass( "h1" );
    stylesClass.addStyle( "font-size" , "16pt" );
    stylesClass.addStyle( "margin-top" , "40px" );
    m_defaultListOfCSSStylesForResourceDescription.addStylesForCSSClass( stylesClass );
  }

  void C2SRestResourceAPIDocumentCreateDefaultStyles::createStylesForH2()
  {
    C2SRestResourceAPIDocumentStylesClass stylesClass( "h2" );
    stylesClass.addStyle( "font-size" , "14pt" );
    m_defaultListOfCSSStylesForResourceDescription.addStylesForCSSClass( stylesClass );
  }

  void C2SRestResourceAPIDocumentCreateDefaultStyles::createStylesForResourceBrief()
  {
    C2SRestResourceAPIDocumentStylesClass stylesClass( "div div" );
    stylesClass.addStyle( "padding" , "0px 20px" );
    m_defaultListOfCSSStylesForResourceDescription.addStylesForCSSClass( stylesClass );
  }

}
