FROM alpine:latest
RUN apk -U upgrade && apk add --no-cache git clang g++ rapidjson-dev libstdc++ wget cmake make meson && \
  wget https://github.com/amrayn/easyloggingpp/archive/refs/tags/v9.97.0.tar.gz && \
  tar -xf v9.97.0.tar.gz && cd easyloggingpp-9.97.0 && \
  mkdir -p build && cd build && cmake -Dbuild_static_lib=ON -Dlib_utc_datetime=ON .. && make && make install && \
  cd ../.. && rm -r easyloggingpp-9.97.0 v9.97.0.tar.gz && \
  git clone https://github.com/pistacheio/pistache.git && \
  cd pistache && \
  meson setup build && \
  meson install -C build && \
  cd .. && rm -r pistache && \
  apk del --purge --no-cache g++ clang wget cmake make meson

COPY . pistache
RUN apk add --no-cache g++ clang cmake make && \   
  export CXX=clang++ && export CC=clang && \
  cd pistache && mkdir -p build && cd build && \
  cmake .. -DCMAKE_BUILD_TYPE=Release && \
  make && \
  mv pistachedemo /usr/bin/pistachedemo && \
  cd ../.. && rm -r pistache && \
  apk del --purge --no-cache g++ clang cmake make
CMD ["pistachedemo"]
EXPOSE 8084 8084