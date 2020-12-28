set( LIBRARY_FILES_P610
        api.h api.c )

add_library(sikep610_ref ${LIBRARY_FILES_P610})

add_executable(kat_SIKEp610 PQCtestKAT_kem.c)

target_link_libraries(kat_SIKEp610 sikep610_ref sike_ref_for_test)
