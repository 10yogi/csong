# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.contrib import admin

# Register your models here.
from .models import Album,Song
admin.site.register(Album)
admin.site.register(Song)

