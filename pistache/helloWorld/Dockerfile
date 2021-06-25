FROM alpine:latest
RUN apk -U upgrade && apk add --no-cache git clang g++ rapidjson-dev libstdc++ meson && \
  git clone https://github.com/pistacheio/pistache.git && \
  cd pistache && \
  meson setup build && \
  meson install -C build && \
  cd - && rm -r pistache && \
  apk del --no-cache --purge g++ clang meson

COPY . pistache
RUN apk add --no-cache g++ clang cmake make && \   
  export CXX=clang++ && export CC=clang && \
  cd pistache && mkdir build && cd build && \
  cmake .. -DCMAKE_BUILD_TYPE=Release && \
  make && \
  mv pistachedemo /usr/bin/pistachedemo && \
  cd ../.. && rm -r pistache && \
  apk del --no-cache --purge g++ clang cmake make
CMD ["pistachedemo"]
EXPOSE 8084 8084