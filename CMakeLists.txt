cmake_minimum_required(VERSION 3.5)

project(stk VERSION 4.6.0 LANGUAGES CXX)

# Add a library with the above sources
add_library(${PROJECT_NAME} STATIC
    src/Stk.cpp
    src/Noise.cpp
    src/Blit.cpp
    src/BlitSaw.cpp
    src/BlitSquare.cpp
    src/Granulate.cpp
    src/Envelope.cpp
    src/ADSR.cpp
    src/Asymp.cpp
    src/Modulate.cpp
    src/SineWave.cpp
    src/FileLoop.cpp
    src/SingWave.cpp
    src/FileRead.cpp
    src/FileWrite.cpp
    src/FileWvIn.cpp
    src/FileWvOut.cpp
    src/Fir.cpp
    src/Iir.cpp
    src/OneZero.cpp
    src/OnePole.cpp
    src/PoleZero.cpp
    src/TwoZero.cpp
    src/TwoPole.cpp
    src/BiQuad.cpp
    src/FormSwep.cpp
    src/Delay.cpp
    src/DelayL.cpp
    src/DelayA.cpp
    src/PRCRev.cpp
    src/JCRev.cpp
    src/NRev.cpp
    src/FreeVerb.cpp
    src/Chorus.cpp
    src/Echo.cpp
    src/PitShift.cpp
    src/LentPitShift.cpp
    src/Voicer.cpp
    src/Sphere.cpp
    src/Twang.cpp
    src/Guitar.cpp
    src/Clarinet.cpp
    src/BlowHole.cpp
    src/Saxofony.cpp
    src/Flute.cpp
    src/Brass.cpp
    src/BlowBotl.cpp
    src/Bowed.cpp
    src/Plucked.cpp
    src/StifKarp.cpp
    src/Sitar.cpp
    src/Mandolin.cpp
    src/Mesh2D.cpp
    src/FM.cpp
    src/Rhodey.cpp
    src/Wurley.cpp
    src/TubeBell.cpp
    src/HevyMetl.cpp
    src/PercFlut.cpp
    src/BeeThree.cpp
    src/FMVoices.cpp
    src/Sampler.cpp
    src/Moog.cpp
    src/Simple.cpp
    src/Drummer.cpp
    src/Shakers.cpp
    src/Modal.cpp
    src/ModalBar.cpp
    src/BandedWG.cpp
    src/Resonate.cpp
    src/VoicForm.cpp
    src/Phonemes.cpp
    src/Whistle.cpp
    src/Messager.cpp
    src/Skini.cpp
    src/MidiFileIn.cpp
    src/RtMidi.cpp
    src/RtWvOut.cpp
    src/Mutex.cpp
    src/RtAudio.cpp
)

add_library(lohi::stk ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

if(NOT CMAKE_SYSTEM_PROCESSOR MATCHES armv7l)
    set(ADITIONAL_LIBS __UNIX_JACK__)
endif()

target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<STREQUAL:$<CONFIGURATION>,Debug>:
        _STK_DEBUG_ __RTAUDIO_DEBUG__ __RTMIDI_DEBUG__>
    PUBLIC __LINUX_ALSA__ ${ADITIONAL_LIBS}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

target_compile_options(${PROJECT_NAME}
    PRIVATE $<$<STREQUAL:$<CONFIGURATION>,Release>:
        -ffast-math -fno-unsafe-math-optimizations -Wall -Wno-psabi > #-Wno-psabi in gcc 7.1 https://stackoverflow.com/a/48149400
    PRIVATE $<$<STREQUAL:$<CONFIGURATION>,Debug>:
        -Wall >
)
