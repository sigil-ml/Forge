import click


@click.command()
@click.option('--depth', default=2, help='Test autodiscovery depth')
def cli(depth):
    print(depth)
