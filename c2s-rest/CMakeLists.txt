cmake_minimum_required( VERSION 2.6 )

include_directories(
  ${C2S_PROJECT_ROOT_DIR}/c2s-http
  ${C2S_PROJECT_ROOT_DIR}/c2s-core
  ${C2S_PROJECT_ROOT_DIR}/c2s-util
  ${C2S_PROJECT_ROOT_DIR}/c2s-util/io
  .
  description
)

add_library( c2s_rest
  C2SRestPathSegment
  C2SRestPathParameter
  C2SRestPathSegmentList
  C2SRestMethodPrototype
  C2SRestResourcePrototype
  C2SRestMatchMethodToRequest
  description/C2SRestResourceDescription
  description/C2SRestResourceDescriptionHTMLHeader
  description/C2SRestResourceDescriptionStylesList
  description/C2SRestResourceDescriptionStylesClass
  description/C2SRestResourceDescriptionCreateDefaultStyles
)

install( TARGETS c2s_rest DESTINATION lib )

add_subdirectory( test )
