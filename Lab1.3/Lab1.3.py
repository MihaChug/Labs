from grab import Grab
from urllib.parse import urlparse, urljoin
import os
import re
import time

word_to_search = 'Путин'
tag_re = re.compile(r'<[^>]+>')
queue = []
ready = []
bad = []
file_name = 'index{}.html'
file_count = 0


def remove_tags(text):
    return tag_re.sub('', text)


def dir_name(url):
    host = urlparse(url).hostname.replace('.', '_')
    if not os.path.exists(host):
        os.mkdir(host)
    return host


def to_next_page():
    if len(queue) > 0:
        # time.sleep(0.5)
        next_page = queue.pop()
        try:
            print('Start with:', next_page)
            spider(next_page)
        except:
            print('Error with:', next_page)
            bad.append(next_page)
            to_next_page()


def spider(site_url):
    host = dir_name(site_url)
    main_host = urlparse(site_url).hostname
    g = Grab()
    resp = g.go(site_url)
    our_links = g.xpath_list('//a/@href')
    for i in range(len(our_links)):
        our_links[i] = remove_tags(our_links[i])
        url_host = urlparse(our_links[i]).hostname
        # старое условие url_host[-( 1 + len(main_host)):] == '.' + main_host
        if '@' not in our_links[i] and (url_host == None or url_host == main_host) and urljoin(site_url, our_links[
            i]) not in bad and urljoin(site_url, our_links[i]) not in queue and urljoin(site_url,
                                                                                        our_links[i]) not in ready:
            # print(our_links[i],'=',ready)
            if url_host == None:
                our_links[i] = urljoin(site_url, our_links[i])
            queue.append(our_links[i])
        # print('append:',our_links[i])
    if g.search(word_to_search):
        page_saver(site_url)
        print('YES!!!')
    ready.append(site_url)
    if site_url in queue:
        queue.remove(site_url)
    save_data()


# to_next_page()

def page_saver(url):
    if (url == None):
        print('Error:url is None')
    host = dir_name(url)
    for fdir in ['img', 'js', 'css']:
        if not os.path.exists(host + '/' + fdir):
            os.mkdir(host + '/' + fdir)
    g = Grab()
    resp = g.go(url)
    # print(resp.headers)
    page_body = g.response.unicode_body()

    if g.search('Путин'):
        list = {}
        list['img'] = g.xpath_list('//img/@src')
        list['js'] = g.xpath_list('//script/@src')
        list['css'] = g.xpath_list('//link/@href')

        for fdir in ['img', 'js', 'css']:
            for file in list[fdir]:

                file_name = os.path.split(urlparse(file).path)[1]
                # print(host + '/' + fdir + '/' + file_name)
                if file_name != '':
                    if not os.path.exists(host + '/' + fdir + '/' + file_name):
                        resp = g.go(file)
                        open(host + '/' + fdir + '/' + file_name, 'wb').write(resp.body)
                    page_body = page_body.replace(file, ('./' + fdir + '/' + file_name))
        global file_count
        file_count += 1
        page = open(host + '/' + 'index{}.html'.format(file_count), 'wb')
        page.write(page_body.encode('utf-8'))
        page.close()


page_url = 'http://lenta.ru/'
host = dir_name(page_url)


def load_data():
    global bad
    global ready
    global queue
    # load index
    if os.path.exists(host + '/bad.txt'):
        file = open(host + '/bad.txt', 'r')
        bad = file.read().split(';')
        file.close()
        print('Bad {} urls is loaded'.format(len(bad)))

    if os.path.exists(host + '/ready.txt'):
        file = open(host + '/ready.txt', 'r')
        ready = file.read().split(';')
        file.close()
        print('Good {} urls is loaded'.format(len(ready)))

    if os.path.exists(host + '/queue.txt'):
        file = open(host + '/queue.txt', 'r')
        queue = file.read().split(';')
        file.close()
        print('Queue {} urls is loaded'.format(len(queue)))


def save_data():
    for listname, list in {'bad': bad, 'ready': ready, 'queue': queue}.items():
        file = open(host + '/{}.txt'.format(listname), 'w')
        file.write(';'.join(list))
        file.close()


load_data()
if len(queue) == 0:
    queue.append(page_url)
while len(queue) > 0:
    next_page = queue.pop()
    try:
        print('Start with:', next_page)
        spider(next_page)
    except:
        print('Error with:', next_page)
        bad.append(next_page)
        to_next_page()

spider(page_url)
save_data()
