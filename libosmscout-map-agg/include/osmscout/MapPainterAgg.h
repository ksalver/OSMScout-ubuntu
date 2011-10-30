#ifndef OSMSCOUT_MAP_MAPPAINTERAGG_H
#define OSMSCOUT_MAP_MAPPAINTERAGG_H

/*
  This source is part of the libosmscout-map library
  Copyright (C) 2011  Tim Teulings

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*/

#include <climits>
#include <cstdlib>

#include <agg2/agg_conv_curve.h>
#include <agg2/agg_conv_contour.h>
#include <agg2/agg_pixfmt_rgb.h>
#include <agg2/agg_rasterizer_scanline_aa.h>
#include <agg2/agg_renderer_base.h>
#include <agg2/agg_rendering_buffer.h>
#include <agg2/agg_renderer_scanline.h>
#include <agg2/agg_scanline_p.h>

// TODO: This one is likely not available under Windows!
#include <agg2/agg_font_freetype.h>

#include <osmscout/private/MapAggImportExport.h>

#include <osmscout/MapPainter.h>

namespace osmscout {

  class OSMSCOUT_MAP_AGG_API MapPainterAgg : public MapPainter
  {
  public:
    typedef agg::pixfmt_rgb24                                  AggPixelFormat;

  private:
    typedef agg::renderer_base<AggPixelFormat>                 AggRenderBase;
    typedef agg::rasterizer_scanline_aa<>                      AggScanlineRasterizer;
    typedef agg::scanline_p8                                   AggScanline;
    typedef agg::renderer_scanline_aa_solid<AggRenderBase>     AggScanlineRendererAA;
    typedef agg::renderer_scanline_bin_solid<AggRenderBase>    AggScanlineRendererBin;

    typedef agg::font_engine_freetype_int32                    AggFontEngine;
    typedef agg::font_cache_manager<AggFontEngine>             AggFontManager;
    typedef agg::conv_curve<AggFontManager::path_adaptor_type> AggTextCurveConverter;
    typedef agg::conv_contour<AggTextCurveConverter>           AggTextContourConverter;

  private:
    AggPixelFormat          *pf;
    AggRenderBase           *renderer_base;
    AggScanlineRasterizer   *rasterizer;
    AggScanline             *scanlineP8;
    AggScanlineRendererAA   *renderer_aa;
    AggScanlineRendererBin  *renderer_bin;
    AggFontEngine           *fontEngine;
    AggFontManager          *fontCacheManager;
    AggTextCurveConverter   *convTextCurves;
    AggTextContourConverter *convTextContours;

  private:
    void SetFont(const MapParameter& parameter,
                 double size);

    void SetOutlineFont(const MapParameter& parameter,
                        double size);

    void GetTextDimension(const std::wstring& text,
                          double& width,
                          double& height);
    void DrawText(double x,
                  double y,
                  const std::wstring& text);

    void DrawOutlineText(double x,
                         double y,
                         const std::wstring& text,
                         double width);

  protected:
    bool HasIcon(const StyleConfig& styleConfig,
                 const MapParameter& parameter,
                 IconStyle& style);

    void GetTextDimension(const MapParameter& parameter,
                          double fontSize,
                          const std::string& text,
                          double& xOff,
                          double& yOff,
                          double& width,
                          double& height);

    void DrawLabel(const Projection& projection,
                   const MapParameter& parameter,
                   const Label& label);

    void DrawPlateLabel(const Projection& projection,
                        const MapParameter& parameter,
                        const Label& label);

    void DrawContourLabel(const Projection& projection,
                          const MapParameter& parameter,
                          const LabelStyle& style,
                          const std::string& text,
                          size_t transStart, size_t transEnd);

    void DrawIcon(const IconStyle* style,
                          double x, double y);

    void DrawSymbol(const SymbolStyle* style,
                            double x, double y);

    void DrawPath(const Projection& projection,
                  const MapParameter& parameter,
                  double r, double g, double b, double a,
                  double width,
                  const std::vector<double>& dash,
                  CapStyle startCap,
                  CapStyle endCap,
                  size_t transStart, size_t transEnd);

    void DrawArea(const Projection& projection,
                  const MapParameter& parameter,
                  const AreaData& area);

    void DrawArea(const FillStyle& style,
                  const MapParameter& parameter,
                  double x,
                  double y,
                  double width,
                  double height);

  public:
    MapPainterAgg();
    virtual ~MapPainterAgg();


    bool DrawMap(const StyleConfig& styleConfig,
                 const Projection& projection,
                 const MapParameter& parameter,
                 const MapData& data,
                 AggPixelFormat* pf);
  };
}

#endif