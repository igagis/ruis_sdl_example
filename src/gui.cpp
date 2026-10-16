#include "gui.hpp"

#include <ruis/widget/button/push_button.hpp>
#include <ruis/widget/input/impl/nine_patch_text_field.hpp>
#include <ruis/widget/label/text.hpp>

using namespace std::string_literals;
using namespace std::string_view_literals;
using namespace ruis::length_literals;

namespace {
constexpr auto text_field_width = 200_pp;
} // namespace

namespace m {
using namespace ruis::make;
} // namespace m

utki::shared_ref<ruis::widget> make_root_widget(const utki::shared_ref<ruis::context> c)
{
	// clang-format off
    return m::pile(c,
        {},
        {
            m::column(c,
                {},
                {
                    m::push_button(c,
                        {
                            .widget{
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
                            .widget{
                                .id = "info_text"s // we can find this label by id from code
                            }
                        },
                        U"Information"s
                    ),
                    m::nine_patch_text_field(c,
                        {
                            .layout_params{
                                .dims{text_field_width, ruis::dim::min}
                            },
                            .widget{
                                .id = "text_input"s
                            }
                        },
                        U"enter text here"s
                    )
                }
            )
        }
    );
	// clang-format on
}
