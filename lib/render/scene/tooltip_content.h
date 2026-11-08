#pragma once

#include "render/core/renderer.h"

#include <cstdint>
#include <memory>
#include <string>
#include <variant>
#include <vector>

struct TooltipRow {
  std::string key;
  std::string value;
  TextEllipsize valueEllipsize = TextEllipsize::End;
};

enum class TooltipPlacement : std::uint8_t {
  Default,
  Above,
  Below,
  Left,
  Right,
};

struct TooltipAnchorInsets {
  float top = 0.0F;
  float right = 0.0F;
  float bottom = 0.0F;
  float left = 0.0F;
};

// Logical size of one window thumbnail in a preview tooltip; images are fitted inside it.
inline constexpr float kTooltipPreviewThumbWidth = 220.0F;
inline constexpr float kTooltipPreviewThumbHeight = 138.0F;

struct TooltipPreviewItem {
  std::string title;
  // Straight RGBA, 4 bytes per pixel with no row padding; null shows a placeholder instead.
  std::shared_ptr<const std::vector<std::uint8_t>> rgba;
  int width = 0;
  int height = 0;
};

// A row of window thumbnails, each captioned with its title.
struct TooltipPreview {
  std::vector<TooltipPreviewItem> items;
};

using TooltipContent = std::variant<std::monostate, std::string, std::vector<TooltipRow>, TooltipPreview>;
