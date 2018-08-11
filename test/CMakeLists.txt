
if (ENABLE_SPLASH)

  if (HAVE_NANOSLEEP OR LIB_RT_HAS_NANOSLEEP)
    set (perf_test_SRCS
      perf-test.cc
      perf-test-preview-dummy.cc
    )
    add_executable(perf-test ${perf_test_SRCS})
    target_link_libraries(perf-test poppler)
    if (LIB_RT_HAS_NANOSLEEP)
      target_link_libraries(perf-test rt)
    endif ()
  endif ()

endif ()

if (GTK_FOUND)

  include_directories(
    SYSTEM
    ${GTK3_INCLUDE_DIRS}
  )

  include_directories(
    ${CMAKE_SOURCE_DIR}/glib
    ${CMAKE_BINARY_DIR}/glib
  )

  set (gtk_splash_test_SRCS
    gtk-test.cc
  )
  poppler_add_test(gtk-test BUILD_GTK_TESTS ${gtk_splash_test_SRCS})
  target_link_libraries(gtk-test ${CAIRO_LIBRARIES} poppler-glib ${GTK3_LIBRARIES})

  if (HAVE_CAIRO)

    set (pdf_inspector_SRCS
      pdf-inspector.cc
    )
    poppler_add_test(pdf-inspector BUILD_GTK_TESTS ${pdf_inspector_SRCS})
    target_link_libraries(pdf-inspector ${CAIRO_LIBRARIES} poppler-glib ${GTK3_LIBRARIES})

  endif ()

endif ()

set (pdf_fullrewrite_SRCS
  pdf-fullrewrite.cc
  ../utils/parseargs.cc
)
add_executable(pdf-fullrewrite ${pdf_fullrewrite_SRCS})
target_link_libraries(pdf-fullrewrite poppler)

find_package(Boost 1.67 REQUIRED COMPONENTS unit_test_framework)

add_executable(test-htmlstring
	test-htmlstring.cc
	../utils/HtmlOutputDev.cc
	../utils/HtmlLinks.cc
	../utils/HtmlFonts.cc
	../utils/devanagari.cc)
target_link_libraries(test-htmlstring poppler Boost::unit_test_framework)
target_include_directories(test-htmlstring PRIVATE "${CMAKE_SOURCE_DIR}/utils")
add_test(NAME test_htmlstring COMMAND test-htmlstring)

add_executable(test-devanagari test-devanagari.cc
	../utils/HtmlOutputDev.cc
	../utils/HtmlLinks.cc
	../utils/HtmlFonts.cc
	../utils/devanagari.cc)
	target_link_libraries(test-devanagari poppler Boost::unit_test_framework)
	target_include_directories(test-devanagari PRIVATE "${CMAKE_SOURCE_DIR}/utils")
add_test(NAME test-devanagari COMMAND test-devanagari)
