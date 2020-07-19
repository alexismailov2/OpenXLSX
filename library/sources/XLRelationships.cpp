//
// Created by Troldal on 25/07/16.
//

#include "XLRelationships.hpp"

#include "XLDocument.hpp"

#include <algorithm>

using namespace std;
using namespace OpenXLSX;

namespace
{
    XLRelationshipType GetTypeFromString(const std::string& typeString)
    {
        XLRelationshipType type;

        if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties")
            type = XLRelationshipType::ExtendedProperties;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/custom-properties")
            type = XLRelationshipType::CustomProperties;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument")
            type = XLRelationshipType::Workbook;
        else if (typeString == "http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties")
            type = XLRelationshipType::CoreProperties;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet")
            type = XLRelationshipType::Worksheet;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles")
            type = XLRelationshipType::Styles;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/sharedStrings")
            type = XLRelationshipType::SharedStrings;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/calcChain")
            type = XLRelationshipType::CalculationChain;
        else if (typeString == "http://schemas.microsoft.com/office/2006/relationships/vbaProject")
            type = XLRelationshipType::VBAProject;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/externalLink")
            type = XLRelationshipType::ExternalLink;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/theme")
            type = XLRelationshipType::Theme;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/chartsheet")
            type = XLRelationshipType::ChartSheet;
        else if (typeString == "http://schemas.microsoft.com/office/2011/relationships/chartStyle")
            type = XLRelationshipType::ChartStyle;
        else if (typeString == "http://schemas.microsoft.com/office/2011/relationships/chartColorStyle")
            type = XLRelationshipType::ChartColorStyle;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/drawing")
            type = XLRelationshipType::Drawing;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image")
            type = XLRelationshipType::Image;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/chart")
            type = XLRelationshipType::Chart;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/externalLinkPath")
            type = XLRelationshipType::ExternalLinkPath;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/printerSettings")
            type = XLRelationshipType::PrinterSettings;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/vmlDrawing")
            type = XLRelationshipType::VMLDrawing;
        else if (typeString == "http://schemas.openxmlformats.org/officeDocument/2006/relationships/ctrlProp")
            type = XLRelationshipType::ControlProperties;
        else
            type = XLRelationshipType::Unknown;

        return type;
    }

    std::string GetStringFromType(XLRelationshipType type)
    {
        string typeString;

        if (type == XLRelationshipType::ExtendedProperties)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties";
        else if (type == XLRelationshipType::CustomProperties)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/custom-properties";
        else if (type == XLRelationshipType::Workbook)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument";
        else if (type == XLRelationshipType::CoreProperties)
            typeString = "http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties";
        else if (type == XLRelationshipType::Worksheet)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet";
        else if (type == XLRelationshipType::Styles)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles";
        else if (type == XLRelationshipType::SharedStrings)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/sharedStrings";
        else if (type == XLRelationshipType::CalculationChain)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/calcChain";
        else if (type == XLRelationshipType::VBAProject)
            typeString = "http://schemas.microsoft.com/office/2006/relationships/vbaProject";
        else if (type == XLRelationshipType::ExternalLink)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/externalLink";
        else if (type == XLRelationshipType::Theme)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/theme";
        else if (type == XLRelationshipType::ChartSheet)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/chartsheet";
        else if (type == XLRelationshipType::ChartStyle)
            typeString = "http://schemas.microsoft.com/office/2011/relationships/chartStyle";
        else if (type == XLRelationshipType::ChartColorStyle)
            typeString = "http://schemas.microsoft.com/office/2011/relationships/chartColorStyle";
        else if (type == XLRelationshipType::Drawing)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/drawing";
        else if (type == XLRelationshipType::Image)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image";
        else if (type == XLRelationshipType::Chart)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/chart";
        else if (type == XLRelationshipType::ExternalLinkPath)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/externalLinkPath";
        else if (type == XLRelationshipType::PrinterSettings)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/printerSettings";
        else if (type == XLRelationshipType::VMLDrawing)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/vmlDrawing";
        else if (type == XLRelationshipType::ControlProperties)
            typeString = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/ctrlProp";
        else
            throw XLException("RelationshipType not recognized!");

        return typeString;
    }

    uint32_t GetNewRelsID(XMLNode relationshipsNode)
    {
        return stoi(string(max_element(relationshipsNode.children().begin(),
                                       relationshipsNode.children().end(),
                                       [](XMLNode a, XMLNode b) {
                                           return stoi(string(a.attribute("Id").value()).substr(3)) <
                                                  stoi(string(b.attribute("Id").value()).substr(3));
                                       })
                               ->attribute("Id")
                               .value())
                        .substr(3)) +
               1;
    }
}    // namespace

/**
 * @details Constructor. Initializes the member variables for the new XLRelationshipItem object.
 */
XLRelationshipItem::XLRelationshipItem(XMLNode node) : m_relationshipNode(node) {}

/**
 * @details Returns the m_relationshipType member variable by value.
 */
XLRelationshipType XLRelationshipItem::Type() const
{
    return GetTypeFromString(m_relationshipNode.attribute("Type").value());
}

/**
 * @details Returns the m_relationshipTarget member variable by value.
 */
std::string XLRelationshipItem::Target() const
{
    return m_relationshipNode.attribute("Target").value();
}

/**
 * @details Returns the m_relationshipId member variable by value.
 */
std::string XLRelationshipItem::Id() const
{
    return m_relationshipNode.attribute("Id").value();
}

/**
 * @details Creates a XLRelationships object, which will read the XML file with the given path
 */
XLRelationships::XLRelationships(XLXmlData* xmlData) : XLXmlFile(xmlData) {}

/**
 * @details Returns the XLRelationshipItem with the given ID, by looking it up in the m_relationships map.
 */
XLRelationshipItem XLRelationships::RelationshipByID(const std::string& id) const
{
    return XLRelationshipItem(XmlDocument().document_element().find_child_by_attribute("Id", id.c_str()));
}

/**
 * @details Returns the XLRelationshipItem with the requested target, by iterating through the items.
 */
XLRelationshipItem XLRelationships::RelationshipByTarget(const std::string& target) const
{
    return XLRelationshipItem(XmlDocument().document_element().find_child_by_attribute("Target", target.c_str()));
}

/**
 * @details Returns a const reference to the internal datastructure (std::map)
 */
std::vector<XLRelationshipItem> XLRelationships::Relationships() const
{
    auto result = std::vector<XLRelationshipItem>();
    for (const auto& item : XmlDocument().document_element().children()) result.emplace_back(XLRelationshipItem(item));

    return result;
}

void XLRelationships::DeleteRelationship(const string& relID)
{
    XmlDocument().document_element().remove_child(XmlDocument().document_element().find_child_by_attribute("Id", relID.c_str()));
}

void XLRelationships::DeleteRelationship(XLRelationshipItem& item)
{
    DeleteRelationship(item.Id());
}

/**
 * @details Adds a new relationship by creating new XML node in the .rels file and creating a new XLRelationshipItem
 * based on the newly created node.
 */
XLRelationshipItem XLRelationships::AddRelationship(XLRelationshipType type, const std::string& target)
{
    string typeString = GetStringFromType(type);

    string id = "rId" + to_string(GetNewRelsID(XmlDocument().document_element()));

    // Create new node in the .rels file
    auto node = XmlDocument().document_element().append_child("Relationship");
    node.append_attribute("Id").set_value(id.c_str());
    node.append_attribute("Type").set_value(typeString.c_str());
    node.append_attribute("Target").set_value(target.c_str());

    if (type == XLRelationshipType::ExternalLinkPath) {
        node.append_attribute("TargetMode").set_value("External");
    }

    return XLRelationshipItem(node);
}

/**
 * @details
 */
bool XLRelationships::TargetExists(const std::string& target) const
{
    return XmlDocument().document_element().find_child_by_attribute("Target", target.c_str()) != nullptr;
}

/**
 * @details
 */
bool XLRelationships::IdExists(const std::string& id) const
{
    return XmlDocument().document_element().find_child_by_attribute("Id", id.c_str()) != nullptr;
}
