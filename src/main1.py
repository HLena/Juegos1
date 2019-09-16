import os, sys , pygame
from random import randint

# type_enemies = ['zombie.jpg','fantasma.jpg','monstrou.jpg']
type_enemies = ['zombicito.jpg','girasolito.jpg','paltita.jpg']

# class Avatar():
#     def __init__(self,x,y,name):
#         self.pos_x = x
#         self.pos_y = y
#         self.state = 1
#         self.type = name
#         self.life = 100



class Projectile(pygame.sprite.Sprite):
    def __init__(self, pos_x,pos_y):
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.Surface((10,10)).convert()
        self.image.fill((255,255,255))
        self.rect = self.image.get_rect()
        self.rect.center = (pos_x,pos_y)
        self.speed_x = 0

    def start(self, speed_x):
        self.speed_x = speed_x
    def update(self):
        self.rect.move_ip(self.speed_x*-1,0)
        if self.rect.x < 0:
            self.kill()
            # print("muerto")

class Enemy(pygame.sprite.Sprite):
    def __init__(self,image,x,y):
        pygame.sprite.Sprite.__init__(self)
        self.pos_x = x
        self.pos_y = y
        self.state = 1
        self.type = image
        self.life = 100
        self.pixel_x = 0
        self.pixel_x = 0
        self.rect = self.type.get_rect()
        self.rect.center = (x,y)
    def update_life(self):
        attack_power = 30
        self.life =self.life - attack_power

    def update(self):
        # attack_power = 10
        # self.life =self.life - attack_power
        if(self.life <= 0 ):
            self.state = 0 
            # print(self.life)
        else:
            print(self.life)
        #     screen.blit(self.type,(self.pos_x,self.pos_y))

class Player():
    def __init__(self,image):
        self.pos_x = 900
        self.pos_y = 400
        self.state = 1
        self.life = 100
        self.image = image
        self.attack_power = 10
        self.speed = 5
    
    def move_up(self):
        self.pos_y += self.speed * -1
    def move_down(self):
        self.pos_y += self.speed * 1
    def move_left(self):
        self.pos_x += self.speed * -1
    def move_right(self):
        self.pos_x += self.speed * 1
    

#===========================metodos===================
def LoadImage(nameImage):
    images_path = os.path.join(
    os.path.dirname(__file__),'../assets','graphics')
    return pygame.image.load(os.path.join(images_path,nameImage)).convert()

def Load(num):
    objects = []
    for i in range(num):
        i = randint(0,2)
        # enemy_image = pygame.image.load(os.path.join(images_path,type_enemies[i])).convert()
        enemy_image =LoadImage(type_enemies[i])
        # print(enemy_image.get_rect().size)
        obj = Enemy(enemy_image,randint(0,200),randint(0,700))
        # objects.add(obj)
        objects.append(obj)
    return objects


#============================funcion main======================
def main():
    pygame.init()
    size = width , height = 1000,800
    screen = pygame.display.set_mode(size)
    pygame.display.set_caption('My first Pygame')

    try: 
        images_path = os.path.join(
            os.path.dirname(__file__),'../assets','graphics')
        # background_image= pygame.image.load(os.path.join(images_path,'background.png')).convert()
        player_image = pygame.image.load(os.path.join(images_path,'paltita.jpg')).convert()
    except pygame.error as e:
        print('Error al cargar la imagen:')
        raise SystemExit(str(e))

    # screen.blit(background_image,(0,0))
    bullets = pygame.sprite.Group()
    enemies = pygame.sprite.Group()

    objects= Load(5)  # lista de enemigos
    player = Player()player_image
    # enemies.add()
    for obj in objects:
        enemies.add(obj)

    clock = pygame.time.Clock()
    fps = 60
    pygame.key.set_repeat(1,1000/fps)

    while True:
        clock.tick(fps)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_UP:
                player.move_up()
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_DOWN:
                player.move_down()
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_LEFT:
                player.move_left()
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_RIGHT:
                player.move_right()
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
                b = Projectile(player.pos_x,player.pos_y)
                b.start(randint(20,50))
                bullets.add(b)
        
        enemies.update()
        # screen.blit(self.type,(self.pos_x,self.pos_y))
        bullets.update()
        bullets.draw(screen)
            
        # for obj in enemies:
        #     screen.blit(obj.type,(obj.pos_x, obj.pos_y))

        for alien in enemies:
            if(alien.state):
                screen.blit(alien.type,(alien.pos_x,alien.pos_y))
            # blocks = pygame.sprite.spritecollide(alien,bullets,True)
            for bullet in bullets:
                if pygame.sprite.collide_rect(bullet,alien):
                    alien.update_life()
                    bullet.kill()
                    # alien.update()
            

        
        
        # pygame.display.update()
        screen.blit(player.image,(player.pos_x,player.pos_y))
        # screen.blit(b)

        pygame.time.delay(100)
    
        # sprites.draw(screen)
        pygame.display.flip()
        screen.fill([0, 0, 0])

if __name__ == '__main__':
    main()

