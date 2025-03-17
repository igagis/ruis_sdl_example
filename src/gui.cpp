#include "gui.hpp"

#include <ruis/widget/button/push_button.hpp>
#include <ruis/widget/label/text.hpp>
#include <ruis/widget/input/text_input_line.hpp>
#include <ruis/widget/label/nine_patch.hpp>

using namespace std::string_literals;
using namespace std::string_view_literals;
using namespace ruis::length_literals;

namespace m{
using namespace ruis::make;
}

utki::shared_ref<ruis::widget> make_root_widget(const utki::shared_ref<ruis::context> c){
    // clang-format off
    return m::pile(c,
        {},
        {
            m::column(c,
                {},
                {
                    m::push_button(c,
                        {
                            .widget_params{
                                .id = "hw_button"s // we can find this label by id from code
                            }
                        },
                        {
                            m::text(c,
                                {},
                                U"Hello world!!!"s
                            )
                        }
                    ),
                    m::text(c,
                        {
                            .widget_params{
                                .id = "info_text"s // we can find this label by id from code
                            }
                        },
                        U"Information"s
                    ),
                    m::nine_patch(c,
                        {
                            .layout_params{
                                .dims{ruis::dim::max, ruis::dim::min}
                            },
                            .widget_params{
                                .id = "text_input"s
                            },
                            .nine_patch_params{
                                .nine_patch = c.get().loader().load<ruis::res::nine_patch>("ruis_npt_textfield_background"sv)
                            }
                        },
                        {
                            m::text_input_line(c,
                                {
                                    .layout_params{
                                        .dims = {200_pp, ruis::dim::min}
                                    }
                                },
                                U"enter text here"s
                            )
                        }
                    )
                }
            )
        }
    );
    // clang-format on
}
