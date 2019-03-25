from django.core.management.base import BaseCommand, CommandError
from questions.models import *


class Command(BaseCommand):
#help = 'Add new questions'

    def add_arguments(self, parser):
        parser.add_argument('N', nargs='+', type=int)

    
    def handle(self, *args, **options):
        for i in options['N']:
            self.stdout.write(self.style.SUCCESS('OK with "%d"' % i)) 
