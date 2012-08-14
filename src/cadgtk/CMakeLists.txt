add_library (cadgtk cad_gtk_adaptor.cpp)
target_link_libraries (cadgtk ${GTK2_LIBRARIES})
target_link_libraries (cadgtk ${Boost_LIBRARIES})
