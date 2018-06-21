
# -*- coding: utf-8 -*-
from __future__ import unicode_literals
from django.views.generic.edit import CreateView,UpdateView,DeleteView
from django.core.urlresolvers import reverse_lazy
from django.shortcuts import render,redirect
from django.contrib.auth import authenticate, login
from django.views import generic
from django.views.generic import View
from .models import Album
from .forms import UserForm
#from .froms import UserForms



# Create your views here.

class IndexView(generic.ListView):
	template_name="music/index.html"
	 
	def get_queryset(self):
	 	return Album.objects.all()

class DetailView(generic.DetailView):
	model = Album
	template_name="music/detail.html"

class AlbumCreate(CreateView):
	model = Album
	fields = ['artist','album_title','genre' ,'album_logo']
	
class AlbumUpdate(UpdateView):
	model = Album
	fields = ['artist', 'album_title', 'genre', 'album_logo']

class AlbumDelete(DeleteView):
	model = Album
	success_url = reverse_lazy('index')

class UserFormView(View):
	form_class = UserForm
	template_name = 'music/registration_form.html'

	#display blank form
	def get(self,request):
		form = self.form_class(None)
		return render(request,self.template_name,{"form":form})
	#pocess form data
	def post(self, request):
		form = self.form_class(request.POST)

		if form.is_valid():

			user = form.save(commit = False)

			# claeaned(normalised) data
			username = form.cleaned_data['username']
			password = form.cleaned_data['password']
			user.set_password(password)
			user.save()

			# returns User objects if credentials are correct
			user = authenticate(username = username, password = password)

			if user is not None:
				if user.is_active:
					login(request, user)
					return redirect('index')

		return render(request, self.template_name,{'form':form})
 


		

