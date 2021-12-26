set(qstm_SRCS
    # cmake-format: sortable
    private/p_qstm_base_setting.cpp
    private/p_qstm_service_manager.cpp
    private/p_qstm_setting_manager.cpp
    qstm_cache_pool.cpp
    qstm_currency.cpp
    qstm_message.cpp
    qstm_object.cpp
    qstm_result.cpp
    qstm_result_info.cpp
    qstm_setting_base.cpp
    qstm_setting_manager.cpp
    qstm_svm.cpp
    qstm_types.cpp
    qstm_url.cpp
    qstm_util_date.cpp
    qstm_util_double.cpp
    qstm_util_formatting.cpp
    qstm_util_meta_object.cpp
    qstm_util_path.cpp
    qstm_util_variant.cpp
    qstm_vvm.cpp

)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    add_library(qstm STATIC ${qstm_SRCS})
else()
    add_library(qstm SHARED ${qstm_SRCS})
endif()

target_link_libraries(
    qstm # cmake-format: sortable
)

install(TARGETS qstm
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/qt/plugins/qstm
)
