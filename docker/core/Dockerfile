FROM siof/sw-core-run-base:latest

USER root

RUN echo 'kernel.core_pattern = core' > /etc/sysctl.d/99-core-pattern

USER core

RUN mkdir -p /server

COPY --chown=core:core dist/ /server/
COPY --chown=core:core scripts/ /server/

RUN mkdir -p /server/bin \
    && mkdir -p /server/conf \
    && mkdir -p /server/etc \
    && mkdir -p /server/data \
    && mkdir -p /server/crashlogs \
    && mkdir -p /server/logs \
    && chmod +x /server/bin/*.sh
