# -*- coding: utf-8 -*-
# Generated by Django 1.11.13 on 2018-06-10 17:23
from __future__ import unicode_literals

from django.db import migrations, models
import django.utils.timezone


class Migration(migrations.Migration):

    dependencies = [
        ('music', '0003_remove_album_album_logo'),
    ]

    operations = [
        migrations.AddField(
            model_name='album',
            name='album_logo',
            field=models.FileField(default=django.utils.timezone.now, upload_to=b''),
            preserve_default=False,
        ),
    ]
