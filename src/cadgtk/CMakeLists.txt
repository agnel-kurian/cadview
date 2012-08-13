add_library (cadcore cad_document.cpp cad_gtk_adaptor.cpp)
target_link_libraries (cadcore ${GTK2_LIBRARIES})
target_link_libraries (cadcore ${Boost_LIBRARIES})
