add_library (cadcore cad_document.cpp cad_gtk_adaptor.cpp)
target_link_libraries (gladeui ${GTK2_LIBRARIES})
target_link_libraries (gladeui ${Boost_LIBRARIES})
