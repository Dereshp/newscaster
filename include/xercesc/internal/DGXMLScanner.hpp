/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xerces" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache\@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation, and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com .  For more information
 * on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/*
 * $Log: DGXMLScanner.hpp,v $
 * Revision 1.3  2003/01/15 15:49:49  knoaman
 * Change constant declaration name to match its value.
 *
 * Revision 1.2  2003/01/13 18:29:41  knoaman
 * Return proper scanner name.
 *
 * Revision 1.1  2002/12/09 15:45:13  knoaman
 * Initial check-in.
 *
 */


#if !defined(DGXMLSCANNER_HPP)
#define DGXMLSCANNER_HPP

#include <xercesc/internal/XMLScanner.hpp>
#include <xercesc/internal/ElemStack.hpp>
#include <xercesc/util/ValueVectorOf.hpp>
#include <xercesc/validators/common/Grammar.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class DTDGrammar;
class DTDValidator;


//  This is an integrated scanner class, which does DTD/XML Schema grammar
//  processing.
class XMLPARSER_EXPORT DGXMLScanner : public XMLScanner
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    DGXMLScanner
    (
        XMLValidator* const valToAdopt
    );
    DGXMLScanner
    (
        XMLDocumentHandler* const  docHandler
        , DocTypeHandler* const    docTypeHandler
        , XMLEntityHandler* const  entityHandler
        , XMLErrorReporter* const  errReporter
        , XMLValidator* const      valToAdopt
    );
    virtual ~DGXMLScanner();

    // -----------------------------------------------------------------------
    //  XMLScanner public virtual methods
    // -----------------------------------------------------------------------
    virtual const XMLCh* getName() const;
    virtual NameIdPool<DTDEntityDecl>* getEntityDeclPool();
    virtual const NameIdPool<DTDEntityDecl>* getEntityDeclPool() const;
    virtual unsigned int resolveQName
    (
        const   XMLCh* const        qName
        ,       XMLBuffer&          prefixBufToFill
        , const short               mode
        ,       int&                prefixColonPos
    );
    virtual void scanDocument
    (
        const   InputSource&    src
    );
    virtual bool scanNext(XMLPScanToken& toFill);
    virtual Grammar* loadGrammar
    (
        const   InputSource&    src
        , const short           grammarType
        , const bool            toCache = false
    );

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DGXMLScanner();
    DGXMLScanner(const DGXMLScanner&);
    void operator=(const DGXMLScanner&);

    // -----------------------------------------------------------------------
    //  XMLScanner virtual methods
    // -----------------------------------------------------------------------
    virtual void scanCDSection();
    virtual void scanCharData(XMLBuffer& toToUse);
    virtual EntityExpRes scanEntityRef
    (
        const   bool    inAttVal
        ,       XMLCh&  firstCh
        ,       XMLCh&  secondCh
        ,       bool&   escaped
    );
    virtual void scanDocTypeDecl();
    virtual void scanReset(const InputSource& src);
    virtual void sendCharData(XMLBuffer& toSend);

    // -----------------------------------------------------------------------
    //  Private helper methods
    // -----------------------------------------------------------------------
    void commonInit();
    void cleanUp();
    InputSource* resolveSystemId(const XMLCh* const sysId); // return owned by caller
    unsigned int buildAttList
    (
        const unsigned int                attCount
        ,       XMLElementDecl*             elemDecl
        ,       RefVectorOf<XMLAttr>&       toFill
    );
    unsigned int resolvePrefix
    (
        const   XMLCh* const        prefix
        , const ElemStack::MapModes mode
    );
    void updateNSMap
    (
        const   XMLCh* const attrPrefix
        , const XMLCh* const attrLocalName
        , const XMLCh* const attrValue
    );
    void scanAttrListforNameSpaces(RefVectorOf<XMLAttr>* theAttrList, int attCount);

    // -----------------------------------------------------------------------
    //  Private scanning methods
    // -----------------------------------------------------------------------
    bool scanAttValue
    (
        const   XMLAttDef* const    attDef
        ,       XMLBuffer&          toFill
    );
    bool scanContent(const bool extEntity);
    void scanEndTag(bool& gotData);
    bool scanStartTag(bool& gotData);
    bool scanStartTagNS(bool& gotData);

    // -----------------------------------------------------------------------
    //  Grammar preparsing methods
    // -----------------------------------------------------------------------
    Grammar* loadDTDGrammar(const InputSource& src, const bool toCache = false);

    // -----------------------------------------------------------------------
    //  Data members
    //
    //  fElemStack
    //      This is the element stack that is used to track the elements that
    //      are currently being worked on.
    //
    //  fRawAttrList
    //      During the initial scan of the attributes we can only do a raw
    //      scan for key/value pairs. So this vector is used to store them
    //      until they can be processed (and put into fAttrList.)
    //
    //  fDTDValidator
    //      The DTD validator instance.
    //
    //  fSchemaValidator
    //      The Schema validator instance.
    //
    //  fSeeXsi
    //      This flag indicates a schema has been seen.
    //
    //  fElemState
    //  fElemStateSize
    //      Stores an element next state from DFA content model - used for
    //      wildcard validation
    //
    //  fMatcherStack
    //      Stack of active XPath matchers for identity constraints. All
    //      active XPath matchers are notified of startElement, characters
    //      and endElement callbacks in order to perform their matches.
    //
    //  fValueStoreCache
    //      Cache of value stores for identity constraint fields.
    //
    //  fFieldActivator
    //      Activates fields within a certain scope when a selector matches
    //      its xpath.
    //
    // -----------------------------------------------------------------------
    ElemStack                   fElemStack;
    ValueVectorOf<XMLAttr*>*    fAttrNSList;
    DTDValidator*               fDTDValidator;
    DTDGrammar*                 fDTDGrammar;
};

inline const XMLCh* DGXMLScanner::getName() const
{
    return XMLUni::fgDGXMLScanner;
}


XERCES_CPP_NAMESPACE_END

#endif
