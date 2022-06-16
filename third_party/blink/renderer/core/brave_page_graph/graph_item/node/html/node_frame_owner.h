/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_THIRD_PARTY_BLINK_RENDERER_CORE_BRAVE_PAGE_GRAPH_GRAPH_ITEM_NODE_HTML_NODE_FRAME_OWNER_H_
#define BRAVE_THIRD_PARTY_BLINK_RENDERER_CORE_BRAVE_PAGE_GRAPH_GRAPH_ITEM_NODE_HTML_NODE_FRAME_OWNER_H_

#include <string>

#include "brave/third_party/blink/renderer/core/brave_page_graph/graph_item/node/html/node_html_element.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace brave_page_graph {

class NodeFrameOwner final : public NodeHTMLElement {
 public:
  NodeFrameOwner(GraphItemContext* context,
                 const blink::DOMNodeId dom_node_id,
                 const std::string& tag_name);

  ItemName GetItemName() const override;

  bool IsNodeFrameOwner() const override;
};

}  // namespace brave_page_graph

namespace blink {

template <>
struct DowncastTraits<brave_page_graph::NodeFrameOwner> {
  static bool AllowFrom(const brave_page_graph::NodeHTMLElement& element_node) {
    return element_node.IsNodeFrameOwner();
  }
  static bool AllowFrom(const brave_page_graph::NodeHTML& html_node) {
    return IsA<brave_page_graph::NodeFrameOwner>(
        DynamicTo<brave_page_graph::NodeHTMLElement>(html_node));
  }
  static bool AllowFrom(const brave_page_graph::GraphNode& node) {
    return IsA<brave_page_graph::NodeFrameOwner>(
        DynamicTo<brave_page_graph::NodeHTML>(node));
  }
  static bool AllowFrom(const brave_page_graph::GraphItem& graph_item) {
    return IsA<brave_page_graph::NodeFrameOwner>(
        DynamicTo<brave_page_graph::GraphNode>(graph_item));
  }
};

}  // namespace blink

#endif  // BRAVE_THIRD_PARTY_BLINK_RENDERER_CORE_BRAVE_PAGE_GRAPH_GRAPH_ITEM_NODE_HTML_NODE_FRAME_OWNER_H_
