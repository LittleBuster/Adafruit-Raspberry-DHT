#!/usr/bin/python
# -*- coding: utf-8 -*-

import os, sys
sys.path.append('/root/DjangoSite/')
os.environ['DJANGO_SETTINGS_MODULE'] = 'DjangoSite.settings'

import django.core.handlers.wsgi

application = django.core.handlers.wsgi.WSGIHandler()
