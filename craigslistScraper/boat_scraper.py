from bs4 import BeautifulSoup
from urllib2 import urlopen
from datetime import datetime
import csv
import sys
import os
import smtplib
import config

BASE_URL = 'http://seattle.craigslist.org/search/boo?min_price={0}&max_price={1}&query={2}'

def parse_results(min_price, max_price, search_term):
    results = []
    search_term = search_term.strip().replace(' ', '+')
    search_url = BASE_URL.format(min_price, max_price, search_term)
    soup = BeautifulSoup(urlopen(search_url).read())
    rows = soup.find('div', 'content').find_all('p', 'row')
    for row in rows:
        url = 'http://seattle.craigslist.org' + row.a['href']
        price = row.find('span', class_='price').get_text()
        create_date = row.find('time').get('datetime')
        title = row.find_all('a')[1].get_text()
        # print('url: %s' % url)
        # print('title: %s' % title)
        # print('price: %s' % price)
        # print('create_date: %s' % create_date)
        results.append({'create_date': create_date, 'url': url, 'title': title, 'price': price})
    return results

def write_results(results):
    """Writes list of dictionaries to file."""
    fields = results[0].keys()
    with open('results.csv', 'w') as f:
        dw = csv.DictWriter(f, fieldnames=fields, delimiter='|')
        dw.writer.writerow(dw.fieldnames)
        dw.writerows(results)

def has_new_records(results):
    current_posts = [x['url'] for x in results]
    fields = results[0].keys()
    if not os.path.exists('results.csv'):
        return True

    with open('results.csv', 'r') as f:
        reader = csv.DictReader(f, fieldnames=fields, delimiter='|')
        seen_posts = [row['url'] for row in reader]

    is_new = False
    for post in current_posts:
        if post in seen_posts:
            pass
        else:
            is_new = True
    return is_new

def send_email_or_text(email, subject, msg):
    fromaddr = "Boat Scraper"
    if email_is_phone_number(email):
        toaddrs = email + "@txt.att.net"
    else:
        toaddrs = email
    msg = ("From: {0}\r\nTo: {1}\r\nSubject: {2}\r\n\r\n{3}").format(fromaddr, toaddrs, subject, msg)
    server = smtplib.SMTP('smtp.gmail.com:587')
    server.ehlo()
    server.starttls()
    server.login(config.email['username'], config.email['password'])
    server.sendmail(fromaddr, toaddrs, msg)
    server.quit()

def get_current_time():
    return datetime.strftime(datetime.now(), '%Y-%m-%d %H:%M:%S')

def email_is_phone_number(email):
    return '@' not in email

if __name__ == '__main__':
    try:
        MIN = sys.argv[1]
        MAX = sys.argv[2]
        TERM = sys.argv[3]
        EMAIL = sys.argv[4].strip().replace('-', '')
    except:
        print("You need to include a MIN, MAX, search term, and 10-digit phone number or email")
        sys.exit(1)

    if email_is_phone_number(EMAIL):
        if len(EMAIL) != 10:
            print("Phone numbers must be 10 digits!\n")
            sys.exit(1)

    results = parse_results(MIN, MAX, TERM)

    # Send SMS msg if there are new results
    if has_new_records(results):
        new_posts_string = "NEW boat_scraper posts for: {0}, MIN={1}, MAX={2}".format(TERM.strip(), MIN, MAX)
        print("[{0}] There are new results - sending message to {1}".format(get_current_time, EMAIL))
        if email_is_phone_number(EMAIL):
            # sending text, just send this
            message = new_posts_string
            subject = ''
        if not email_is_phone_number(EMAIL):
            # emailing, so send full list, with URLs
            subject = new_posts_string
            message = ''
            fields = results[0].keys()
            for result in results:
                message += '\r\n=============================================\r\n'
                for field in fields:
                    message += '\r\n'
                    message += result[field]
        send_email_or_text(EMAIL, subject, message)
        write_results(results)
    else:
        print("[{0}] No new results - will try again later".format(get_current_time()))


